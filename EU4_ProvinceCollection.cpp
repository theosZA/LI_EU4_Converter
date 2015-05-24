#include "EU4_ProvinceCollection.h"

#include <algorithm>
#include <fstream>
#include <stdexcept>

#include "FileUtilities.h"
#include "StringUtilities.h"

namespace EU4 {

ProvinceCollection::ProvinceCollection(const std::set<int> provinceIDs, const std::string& provincePath)
{
  auto provinceFileNames = GetAllFilesInFolder(provincePath);
  for (const auto& provinceFileName : provinceFileNames)
  {
    int provinceID = std::stoi(provinceFileName);
    if (provinceIDs.find(provinceID) != provinceIDs.end())
    {
      auto splitPos = provinceFileName.find('-');
      if (splitPos != std::string::npos)
      {
        auto provinceName = TrimWhitespace(provinceFileName.substr(splitPos + 1));
        std::ifstream provinceSourceFile(provincePath + '\\' + provinceFileName);
        provinces.emplace_back(provinceID, provinceName, provinceSourceFile);
        provinceHistoryFileNames[provinceID] = provinceFileName;
      }
    }
  }
}

const Province& ProvinceCollection::GetProvince(int provinceID) const
{
  return const_cast<const Province&>(const_cast<ProvinceCollection*>(this)->GetProvince(provinceID));
}

Province& ProvinceCollection::GetProvince(int provinceID)
{
  auto findIter = std::find_if(provinces.begin(), provinces.end(), [=](const Province& province) { return province.GetID() == provinceID; });
  if (findIter == provinces.end())
    throw std::runtime_error("Failed to find EU4 province " + std::to_string(provinceID));
  return *findIter;
}

void ProvinceCollection::ResetOwnerForAllProvinces(const std::string& tag)
{
  for (auto& province : provinces)
    province.ResetOwner(tag);
}

void ProvinceCollection::WriteHistoryToFiles(const std::string& path, const CountryCollection& countries) const
{
  for (const auto& province : provinces)
  {
    auto findIter = provinceHistoryFileNames.find(province.GetID());
    if (findIter != provinceHistoryFileNames.end())
    {
      auto provinceFileName = findIter->second;
      std::ofstream provinceFile(path + '\\' + provinceFileName);
      province.WriteHistory(provinceFile, countries);
    }
  }
}

} // EU4