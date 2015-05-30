#include "CK2_CultureGroup.h"

namespace CK2 {

CultureGroup::CultureGroup(const Parser::Item& cultureGroupItem)
: id(cultureGroupItem.key)
{
  for (const auto& item : cultureGroupItem.items)
    if (item->key == "graphical_culture")
      portraitGraphicalCulture = item->value;
    else if (item->key == "second_graphical_culture")
      unitGraphicalCulture = item->value;
    else // a new culture
      cultures.emplace(item->key, Culture(*item, portraitGraphicalCulture, unitGraphicalCulture));
}

} // CK2