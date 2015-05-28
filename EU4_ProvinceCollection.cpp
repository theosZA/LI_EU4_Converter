#include "EU4_ProvinceCollection.h"

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
    auto sourceProvinceID = sourceProvinceIDs[0]; // For now we will just use whichever province is listed first. TBD: Use a real decision algorithm.
    auto sourceTitle = sourceProvinces.GetProvinceTopLevelTitle(sourceProvinceID, titles);
    const auto& country = countries.GetCountryByTitle(sourceTitle);

    destProvince.ResetOwner(country.GetTag());
    LOG(LogLevel::Debug) << "EU4 province " << destProvinceID << " from CK2 province " << sourceProvinceID << " (" << sourceTitle << " to " << country.GetName() << ')';
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