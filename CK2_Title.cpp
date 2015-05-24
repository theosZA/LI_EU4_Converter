#include "CK2_Title.h"

namespace CK2 {

Title::Title(const Parser::Item& titleItem)
: id(titleItem.key)
{
  for (const auto& titleSubItem : titleItem.items)
  {
    if (titleSubItem->key == "liege" && !titleSubItem->items.empty())
    {
      for (const auto& liegeItems : titleSubItem->items)
        if (liegeItems->key == "title")
          liegeTitle = liegeItems->value;
    }
    else if (titleSubItem->key == "holder")
      holderID = std::stoi(titleSubItem->value);
    else if (titleSubItem->key == "succession")
      succession = titleSubItem->value;
  }
}

} // CK2