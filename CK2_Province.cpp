#include "CK2_Province.h"

namespace CK2 {

Province::Province(const Parser::Item& provinceItem)
: id(std::stoi(provinceItem.key))
{
  for (const auto& provinceSubItem : provinceItem.items)
  {
    if (provinceSubItem->key == "name")
      name = provinceSubItem->value;
    else if (provinceSubItem->key == "culture")
      culture = provinceSubItem->value;
    else if (provinceSubItem->key == "religion")
      religion = provinceSubItem->value;
    else if (provinceSubItem->key.size() >= 2 && provinceSubItem->key[0] == 'b' && provinceSubItem->key[1] == '_')
      baronyLevelTitles.insert(provinceSubItem->key);
  }
}

} // CK2