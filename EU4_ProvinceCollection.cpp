#include "EU4_ProvinceCollection.h"

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "CK2_ProvinceCollection.h"
#include "CK2_TitleCollection.h"
#include "EU4_CountryCollection.h"
#include "FileUtilities.h"
#include "LI_EU4_ProvinceMapping.h"
#include "Log.h"
#include "StringUtilities.h"

namespace EU4 {

const std::string& DetermineProvinceOwnership(Province& destProvince, const std::vector<int>& sourceProvinceIDs,
                                              const CK2::ProvinceCollection& sourceProvinces, const CK2::TitleCollection& titles, const CountryCollection& countries)
{
  int maxProvincesOwned = 0;
  // Count how many provinces each title (country) has.
  std::map<std::string, int> provincesOwnedByTitle;
  std::vector<std::string> sourceProvinceOwners;
  for (int sourceProvinceID : sourceProvinceIDs)
  {
    auto titleID = sourceProvinces.GetProvinceTopLevelTitle(sourceProvinceID, titles);
    sourceProvinceOwners.push_back(titleID);
    auto findIter = provincesOwnedByTitle.find(titleID);
    if (findIter == provincesOwnedByTitle.end())
      findIter = provincesOwnedByTitle.emplace(std::move(titleID), 0).first;
    int& provincesOwned = findIter->second;
    ++provincesOwned;
    if (provincesOwned > maxProvincesOwned)
      maxProvincesOwned = provincesOwned;
  }

  // Award cores to all countries with provinces.
  destProvince.ClearCores();
  for (const auto& ownerPair : provincesOwnedByTitle)
  {
    const auto& titleID = ownerPair.first;
    destProvince.AddCore(countries.GetCountryByTitle(titleID).GetTag());
  }

  // Remove from the running (for ownership of the new province) all countries that
  // don't have the most source provinces.
  for (auto i = provincesOwnedByTitle.begin(); i != provincesOwnedByTitle.end();)
    if (i->second < maxProvincesOwned)
      provincesOwnedByTitle.erase(i++);
    else
      ++i;

  // Pick the owner of the first source province in the given list who is still in the running.
  auto bestIter = std::find_if(sourceProvinceOwners.begin(), sourceProvinceOwners.end(),
      [&](const std::string& sourceProvinceOwner)
      {
        return provincesOwnedByTitle.find(sourceProvinceOwner) != provincesOwnedByTitle.end();
      });
  if (bestIter == sourceProvinceOwners.end())
  {
    static const std::string noOwner = "";
    return noOwner;
  }

  const auto& bestOwnerTitle = *bestIter;
  const auto& bestOwnerTag = countries.GetCountryByTitle(bestOwnerTitle).GetTag();
  destProvince.SetOwner(bestOwnerTag);
  destProvince.SetController(bestOwnerTag);
  return countries.GetCountry(bestOwnerTag).GetName();
}

ProvinceCollection::ProvinceCollection(const CK2::ProvinceCollection& sourceProvinces, const CK2::TitleCollection& titles, const CountryCollection& countries,
                                       const std::string& provinceMappingFileName, const std::string& provincePath)
{
  LOG(LogLevel::Info) << "Reading province mapping";
  LI_EU4::ProvinceMapping provinceMapping((std::ifstream(provinceMappingFileName)));

  LOG(LogLevel::Info) << "Reading EU4 provinces";
  ReadProvincesFromFiles(provinceMapping.GetAllEU4ProvinceIDs(), provincePath);

  LOG(LogLevel::Info) << "Converting provinces to EU4";
  for (auto& destProvincePair : provinces)
  {
    auto destProvinceID = destProvincePair.first;
    auto& destProvince = destProvincePair.second;

    const auto& sourceProvinceIDs = provinceMapping.GetCK2ProvinceIDs(destProvinceID);
    const auto& owner = DetermineProvinceOwnership(destProvince, sourceProvinceIDs, sourceProvinces, titles, countries);

    LOG(LogLevel::Debug) << "EU4 province " << destProvinceID << " assigned to " << owner;
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
  return findIter->second;
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
      province.WriteHistory(provinceFile, countries);
    }
  }
}

void ProvinceCollection::ReadProvincesFromFiles(const std::set<int>& provinceIDs, const std::string& path)
{
  auto provinceFileNames = GetAllFilesInFolder(path);
  for (const auto& provinceFileName : provinceFileNames)
  {
    int provinceID = std::stoi(provinceFileName);
    if (provinceIDs.find(provinceID) != provinceIDs.end())
    {
      auto splitPos = provinceFileName.find('-');
      if (splitPos != std::string::npos)
      {
        auto provinceName = TrimWhitespace(provinceFileName.substr(splitPos + 1));
        std::ifstream provinceSourceFile(path + '\\' + provinceFileName);
        Province province(provinceID, provinceName, provinceSourceFile);
        provinces.emplace(provinceID, std::move(province));
        provinceHistoryFileNames[provinceID] = provinceFileName;
      }
    }
  }
}

} // EU4