#include "EU4_ProvinceCollection.h"

#include <fstream>

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
      }
    }
  }
}

void ProvinceCollection::ResetOwnerForAllProvinces(const std::string& tag)
{
  for (auto& province : provinces)
    province.ResetOwner(tag);
}

void ProvinceCollection::WriteHistoryToFiles(const std::string& path, const std::function<std::string(const std::string&)>& tagToName) const
{
  for (const auto& province : provinces)
  {
    std::ofstream provinceFile(path + '\\' + std::to_string(province.GetID()) + '-' + province.GetName() + ".txt");
    province.WriteHistory(provinceFile, tagToName);
  }
}

} // EU4