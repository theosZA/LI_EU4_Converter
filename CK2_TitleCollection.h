#pragma once

#include <map>
#include <string>

#include "CK2_Title.h"
#include "Parser.h"

namespace CK2 {

// Represents all CK2 landed titles in the game.
class TitleCollection
{
  public:
    TitleCollection(const Parser::Item& titlesItem);

  private:
    std::map<std::string, Title> titles;
};

} // CK2