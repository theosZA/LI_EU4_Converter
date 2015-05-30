#include "CK2_ProvinceCollection.h"

#include <fstream>
#include <stdexcept>

#include "FileUtilities.h"
#include "StringUtilities.h"

namespace CK2 {

ProvinceCollection::ProvinceCollection(const Parser::Item& provincesItem, const std::string& historyProvincesPath)
{
  for (const auto& provinceItem : provincesItem.items)
  {
    Province province(*provinceItem);
    provinces.emplace(province.GetID(), std::move(province));
  }

  auto historyFiles = FileUtilities::GetAllFilesInFolder(historyProvincesPath);
  for (const auto& historyFileName : historyFiles)
  {
    const auto& fileNameParts = SplitString(historyFileName, '-');
    if (!fileNameParts.empty())
    {
      int provinceID = std::stoi(TrimWhitespace(fileNameParts.front()));
      auto findIter = provinces.find(provinceID);
      if (findIter != provinces.end())
        findIter->second.UpdateFromHistory(Parser::Parse(std::ifstream(historyProvincesPath + '\\' + historyFileName)));
    }
  }
}

const Province& ProvinceCollection::GetProvince(int provinceID) const
{
  auto findIter = provinces.find(provinceID);
  if (findIter == provinces.end())
    throw std::runtime_error("Failed to find province " + std::to_string(provinceID));
 
  return findIter->second;
}

int ProvinceCollection::GetProvinceIDForCountyLevelTitle(const std::string& titleID) const
{
  for (const auto& provincePair : provinces)
    if (provincePair.second.GetCountyLevelTitleID() == titleID)
      return provincePair.first;
  return -1;
}

} // CK2