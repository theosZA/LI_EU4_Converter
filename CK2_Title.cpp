#include "CK2_Title.h"

namespace CK2 {

std::string StripQuotes(const std::string& text)
{
  if (text.size() >= 2 && text.front() == '"' && text.back() == '"')
    return text.substr(1, text.size() - 2);
  else
    return text;
}

Title::Title(const Parser::Item& titleItem)
: id(titleItem.key)
{
  for (const auto& titleSubItem : titleItem.items)
  {
    if (titleSubItem->key == "liege" && !titleSubItem->items.empty())
    {
      for (const auto& liegeItems : titleSubItem->items)
        if (liegeItems->key == "title")
          liegeTitle = StripQuotes(liegeItems->value);
    }
    else if (titleSubItem->key == "holder")
      holderID = std::stoi(titleSubItem->value);
    else if (titleSubItem->key == "succession")
      succession = titleSubItem->value;
  }
}

} // CK2