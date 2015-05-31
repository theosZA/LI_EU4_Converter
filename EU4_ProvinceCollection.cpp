#include "EU4_ProvinceCollection.h"

#include <algorithm>
#include <fstream>
#include <functional>
#include <stdexcept>
#include <vector>

#include "CK2_ProvinceCollection.h"
#include "CK2_TitleCollection.h"
#include "EU4_CountryCollection.h"
#include "EU4_EmptyProvince.h"
#include "EU4_SettledProvince.h"
#include "FileUtilities.h"
#include "LI_EU4_ProvinceMapping.h"
#include "Log.h"
#include "MapUtilities.h"
#include "Parser.h"
#include "StringUtilities.h"

namespace EU4 {

// Returns true if the given collection has the specified value.
template <class V>
bool HasValue(const std::vector<V>& collection, const V& value)
{
  return std::find(collection.begin(), collection.end(), value) != collection.end();
}

// We are interested in a particular feature of each province. Returns a count of each unique instance of that
// feature across all specified provinces.
std::map<std::string, int> GetProvinceFeatureCounts(const std::vector<int>& sourceProvinceIDs, const CK2::ProvinceCollection& sourceProvinces,
                                                    const std::function<std::string(const CK2::Province&)>& getFeature)
{
  std::map<std::string, int> featureCounts;
  for (int sourceProvinceID : sourceProvinceIDs)
  {
    std::string feature = getFeature(sourceProvinces.GetProvince(sourceProvinceID));
    auto findIter = featureCounts.find(feature);
    if (findIter == featureCounts.end())
      findIter = featureCounts.emplace(std::move(feature), 0).first;
    int& count = findIter->second;
    ++count;
  }
  return featureCounts;
}

// Returns the first province in the list of province IDs for which the predicate returns true.
// Returns 0 if no matching province is found.
int GetFirstProvince(const std::vector<int>& sourceProvinceIDs, const CK2::ProvinceCollection& sourceProvinces,
                     const std::function<bool(const CK2::Province&)>& predicate)
{
  for (int sourceProvinceID : sourceProvinceIDs)
    if (predicate(sourceProvinces.GetProvince(sourceProvinceID)))
      return sourceProvinceID;
  return 0;
}

const std::string& DetermineProvinceOwnership(SettledProvince& destProvince, const std::vector<int>& sourceProvinceIDs,
                                              const CK2::ProvinceCollection& sourceProvinces, const CK2::TitleCollection& titles, const CountryCollection& countries)
{
  // Count how many provinces each title (country) has.
  auto provincesOwnedByTitle = GetProvinceFeatureCounts(sourceProvinceIDs, sourceProvinces, 
      [&](const CK2::Province& sourceProvince) 
      {
        return sourceProvince.GetTopLevelTitle(titles); 
      });

  // Award cores to all countries with provinces.
  destProvince.ClearCores();
  for (const auto& ownerPair : provincesOwnedByTitle)
  {
    const auto& titleID = ownerPair.first;
    destProvince.AddCore(countries.GetCountryByTitle(titleID).GetTag());
  }

  // Remove from the running (for ownership of the new province) all countries that
  // don't have the most source provinces.
  auto bestTitles = MapUtilities::GetKeysWithMaxValue(provincesOwnedByTitle);

  // Pick the owner of the first source province in the given list who is still in the running.
  int bestProvinceID = GetFirstProvince(sourceProvinceIDs, sourceProvinces,
      [&](const CK2::Province& sourceProvince) 
      {
        return HasValue(bestTitles, sourceProvince.GetTopLevelTitle(titles));
      });
  if (bestProvinceID == 0)
  {
    static const std::string noOwner = "";
    return noOwner;
  }

  const auto& bestOwnerTitle = sourceProvinces.GetProvince(bestProvinceID).GetTopLevelTitle(titles);
  const auto& bestOwnerTag = countries.GetCountryByTitle(bestOwnerTitle).GetTag();
  destProvince.SetOwner(bestOwnerTag);
  destProvince.SetController(bestOwnerTag);
  return countries.GetCountry(bestOwnerTag).GetName();
}

const std::string& GetMajorityCulture(const std::vector<int>& sourceProvinceIDs, const CK2::ProvinceCollection& sourceProvinces)
{
  auto numProvincesWithCulture = GetProvinceFeatureCounts(sourceProvinceIDs, sourceProvinces, 
      [&](const CK2::Province& sourceProvince) 
      {
        return sourceProvince.GetCulture(); 
      });
  auto bestCultures = MapUtilities::GetKeysWithMaxValue(numProvincesWithCulture);
  int bestProvinceID = GetFirstProvince(sourceProvinceIDs, sourceProvinces,
      [&](const CK2::Province& sourceProvince) 
      {
        return HasValue(bestCultures, sourceProvince.GetCulture());
      });
  if (bestProvinceID == 0)
  {
    static const std::string noCulture = "";
    return noCulture;
  }
  return sourceProvinces.GetProvince(bestProvinceID).GetCulture();
}

ProvinceCollection::ProvinceCollection(const CK2::ProvinceCollection& sourceProvinces, const CK2::TitleCollection& titles, const CountryCollection& countries,
                                       const std::string& provinceMappingFileName, const std::string& provincePath)
{
  LOG(LogLevel::Info) << "Reading province mapping";
  LI_EU4::ProvinceMapping provinceMapping((std::ifstream(provinceMappingFileName)));

  LOG(LogLevel::Info) << "Reading EU4 provinces";
  ReadProvincesFromFiles(provinceMapping.GetAllEU4SettledProvinceIDs(), provincePath, true);
  ReadProvincesFromFiles(provinceMapping.GetAllEU4EmptyProvinceIDs(), provincePath, false);

  LOG(LogLevel::Info) << "Converting provinces to EU4";
  for (auto& destProvincePair : provinces)
  {
    auto destProvinceID = destProvincePair.first;
    auto& destProvince = destProvincePair.second;
    auto destSettledProvince = dynamic_cast<SettledProvince*>(&*destProvince);
    if (destSettledProvince)
    {
      const auto& sourceProvinceIDs = provinceMapping.GetCK2ProvinceIDs(destProvinceID);
      const auto& owner = DetermineProvinceOwnership(*destSettledProvince, sourceProvinceIDs, sourceProvinces, titles, countries);
      LOG(LogLevel::Debug) << "EU4 province " << destProvinceID << " assigned to " << owner;

      const auto& culture = GetMajorityCulture(sourceProvinceIDs, sourceProvinces);
      destProvince->SetCulture(culture);
      LOG(LogLevel::Debug) << "EU4 province " << destProvinceID << " culture set to " << culture;
    }
  }
}

const Province& ProvinceCollection::GetProvince(int provinceID) const
{
  return const_cast<const Province&>(const_cast<ProvinceCollection*>(this)->GetProvince(provinceID));
}

Province& ProvinceCollection::GetProvince(int provinceID)
{
  auto findIter = provinces.find(provinceID);    
  if (findIter == provinces.end())
    throw std::runtime_error("Failed to find EU4 province " + std::to_string(provinceID));
  return *findIter->second;
}

void ProvinceCollection::WriteHistoryToFiles(const std::string& path, const CountryCollection& countries) const
{
  for (const auto& provincePair : provinces)
  {
    auto provinceID = provincePair.first;
    const auto& province = provincePair.second;
    auto findIter = provinceHistoryFileNames.find(provinceID);
    if (findIter != provinceHistoryFileNames.end())
    {
      auto provinceFileName = findIter->second;
      std::ofstream provinceFile(path + '\\' + provinceFileName);
      province->WriteHistory(provinceFile, countries);
    }
  }
}

void ProvinceCollection::ReadProvincesFromFiles(const std::set<int>& provinceIDs, const std::string& path, bool settled)
{
  auto provinceFileNames = FileUtilities::GetAllFilesInFolder(path);
  for (const auto& provinceFileName : provinceFileNames)
  {
    int provinceID = std::stoi(provinceFileName);
    if (provinceIDs.find(provinceID) != provinceIDs.end())
    {
      auto splitPos = provinceFileName.find('-');
      if (splitPos != std::string::npos)
      {
        auto provinceName = TrimWhitespace(provinceFileName.substr(splitPos + 1));
        auto provinceHistorySource = Parser::Parse(std::ifstream(path + '\\' + provinceFileName));
        std::unique_ptr<Province> province;
        if (settled)
          province.reset(new SettledProvince(provinceID, provinceName, provinceHistorySource));
        else
          province.reset(new EmptyProvince(provinceID, provinceName, provinceHistorySource));
        provinces.emplace(provinceID, std::move(province));
        provinceHistoryFileNames[provinceID] = provinceFileName;
      }
    }
  }
}

} // EU4