#include "CK2_CharacterCollection.h"

#include <stdexcept>

namespace CK2 {

CharacterCollection::CharacterCollection(const Parser::ItemSet& characterItems)
{
  for (const auto& characterItem : characterItems)
  {
    Character character(*characterItem);
    characters.emplace(character.GetID(), std::move(character));
  }
}

const Character& CharacterCollection::GetCharacter(int id) const
{
  auto findIter = characters.find(id);
  if (findIter == characters.end())
    throw std::runtime_error("CK2 character " + std::to_string(id) + " not found");
  return findIter->second;
}

} // CK2