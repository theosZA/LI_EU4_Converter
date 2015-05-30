#include "CK2_CultureCollection.h"

namespace CK2 {

CultureCollection::CultureCollection(const Parser::ItemSet& cultureGroupItems)
{
  for (const auto& item : cultureGroupItems)
    cultureGroups.emplace(item->key, CultureGroup(*item));
}

} // CK2