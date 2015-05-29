#include "CK2_Title.h"

#include "CK2_Localisation.h"

namespace CK2 {

std::string StripQuotes(const std::string& text)
{
  if (text.size() >= 2 && text.front() == '"' && text.back() == '"')
    return text.substr(1, text.size() - 2);
  else
    return text;
}

Title::Title(const Parser::Item& titleItem, const Localisation& localisation)
: id(titleItem.key),
  name(localisation.GetLocalisation(id, 0)),
  adjective(localisation.GetLocalisation(id + "_adj", 0))
{
  if (adjective.empty())
    adjective = name; // fallback as many adjective forms are left unspecified.

  if (name.empty()) // this looks wrong - there should be a name for every title specified somewhere
    name = adjective;

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