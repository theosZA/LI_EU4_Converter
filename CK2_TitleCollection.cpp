#include "CK2_TitleCollection.h"

namespace CK2 {

// Represents all CK2 landed titles in the game.
TitleCollection::TitleCollection(const Parser::Item& titlesItem)
{
  for (const auto& titleItem : titlesItem.items)
  {
    Title title(*titleItem);
    titles.emplace(title.GetID(), std::move(title));
  }
}

} // CK2