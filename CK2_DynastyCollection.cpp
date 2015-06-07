#include "CK2_DynastyCollection.h"

#include <stdexcept>

namespace CK2 {

void DynastyCollection::AddDynasties(const Parser::ItemSet& dynastyItems)
{
  for (const auto& dynastyItem : dynastyItems)
  {
    Dynasty dynasty(*dynastyItem);
    dynasties.emplace(dynasty.GetID(), std::move(dynasty));
  }
}

const Dynasty& DynastyCollection::GetDynasty(int id) const
{
  auto findIter = dynasties.find(id);
  if (findIter == dynasties.end())
    throw std::runtime_error("CK2 dynasty " + std::to_string(id) + " not found");
  return findIter->second;
}

} // CK2