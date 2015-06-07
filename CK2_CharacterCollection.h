#pragma once

#include <map>

#include "CK2_Character.h"
#include "Parser.h"

namespace CK2 {

// Represents all characters in CK2.
class CharacterCollection
{
  public:
    CharacterCollection(const Parser::ItemSet& characterItems);

    const Character& GetCharacter(int id) const;

  private:
    std::map<int, Character> characters;
};

} // CK2