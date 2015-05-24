#pragma once

#include <map>
#include <string>
#include <vector>

#include "CK2_Title.h"
#include "Parser.h"

namespace CK2 {

// Represents all CK2 landed titles in the game.
class TitleCollection
{
  public:
    TitleCollection(const Parser::Item& titlesItem);

    // Returns the top-level liege of the given title; may be the same title.
    std::string GetTopLevelLiege(const std::string& titleID) const;
    // Returns all top-level titles in this collection.
    std::vector<std::string> GetAllTopLevelTitles() const;

  private:
    std::map<std::string, Title> titles;
};

} // CK2