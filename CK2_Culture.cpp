#include "CK2_Culture.h"

#include "StringUtilities.h"

namespace CK2 {

Culture::Culture(const Parser::Item& cultureItem, const std::string& groupPortraitGraphicalCulture, const std::string& groupUnitGraphicalCulture)
: id(cultureItem.key),
  portraitGraphicalCulture(groupPortraitGraphicalCulture),
  unitGraphicalCulture(groupUnitGraphicalCulture)
{
  for (const auto& item : cultureItem.items)
    if (item->key == "graphical_culture")
      portraitGraphicalCulture = item->value;
    else if (item->key == "second_graphical_culture")
      unitGraphicalCulture = item->value;
    else if (item->key == "color" && !item->items.empty())
      colour = Colour::CreateFromFractions(item->items.front()->key);
    else if (item->key == "male_names" && !item->items.empty())
      maleNames = SplitString(item->items.front()->key, ' ');
    else if (item->key == "female_names" && !item->items.empty())
      femaleNames = SplitString(item->items.front()->key, ' ');

  if (unitGraphicalCulture.empty())
    unitGraphicalCulture = portraitGraphicalCulture;
}
        
} // CK2