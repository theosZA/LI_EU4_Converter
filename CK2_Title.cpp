#include "CK2_Title.h"

#include "CK2_Localisation.h"
#include "CK2_ProvinceCollection.h"
#include "StringUtilities.h"

namespace CK2 {

Title::Title(const Parser::Item& titleItem, const Localisation& localisation, const ProvinceCollection& provinces)
: id(titleItem.key),
  name(localisation.GetLocalisation(id, 0)),
  adjective(localisation.GetLocalisation(id + "_adj", 0)),
  holderID(0)
{
  for (const auto& titleSubItem : titleItem.items)
  {
    if (titleSubItem->key == "liege" && !titleSubItem->items.empty())
    {
      for (const auto& liegeItems : titleSubItem->items)
        if (liegeItems->key == "title")
          liegeTitle = StripQuotes(liegeItems->value);
    }
    else if (titleSubItem->key == "name")
      name = StripQuotes(titleSubItem->value);
    else if (titleSubItem->key == "holder")
      holderID = std::stoi(titleSubItem->value);
    else if (titleSubItem->key == "succession")
      succession = titleSubItem->value;
  }

  // Some county-level titles have no name - we default to using the province name as CK2 appears to do.
  if (name.empty())
  {
    int provinceID = provinces.GetProvinceIDForCountyLevelTitle(id);
    if (provinceID != -1)
      name = provinces.GetProvince(provinceID).GetName();
  }

  if (name.empty()) // There really should be a name for every title specified somewhere - for now use the title ID so it stands out.
    name = id;

  if (adjective.empty())
    adjective = name; // Fallback as many adjective forms are left unspecified.
}

} // CK2