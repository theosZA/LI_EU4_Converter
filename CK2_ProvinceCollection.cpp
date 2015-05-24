#include "CK2_ProvinceCollection.h"

namespace CK2 {

ProvinceCollection::ProvinceCollection(const Parser::Item& provincesItem)
{
  for (const auto& provinceItem : provincesItem.items)
  {
    Province province(*provinceItem);
    provinces.emplace(province.GetID(), std::move(province));
  }
}

} // CK2