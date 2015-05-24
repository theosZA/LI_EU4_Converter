#include "CK2_ProvinceCollection.h"

#include <stdexcept>

namespace CK2 {

ProvinceCollection::ProvinceCollection(const Parser::Item& provincesItem)
{
  for (const auto& provinceItem : provincesItem.items)
  {
    Province province(*provinceItem);
    provinces.emplace(province.GetID(), std::move(province));
  }
}

std::string ProvinceCollection::GetProvinceTopLevelTitle(int provinceID, const TitleCollection& titles) const
{
  auto findIter = provinces.find(provinceID);
  if (findIter == provinces.end())
    throw std::runtime_error("Failed to find province " + std::to_string(provinceID));
  
  return findIter->second.GetTopLevelTitle(titles);
}

} // CK2