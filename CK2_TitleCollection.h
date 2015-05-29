#pragma once

#include <map>
#include <string>
#include <vector>

#include "CK2_Title.h"
#include "Parser.h"

namespace CK2 {

class Localisation;

// Represents all CK2 landed titles in the game.
class TitleCollection
{
  public:
    TitleCollection(const Parser::Item& titlesItem, const Localisation&);

    // Updates the titles with the general information provided in the given items, e.g. colour.
    void UpdateTitles(const Parser::ItemSet& items);

    // Returns the top-level liege of the given title; may be the same title.
    std::string GetTopLevelLiege(const std::string& titleID) const;
    // Returns all top-level titles in this collection.
    std::vector<std::string> GetAllTopLevelTitles() const;

    const Title& GetTitle(const std::string& titleID) const;

  private:
    // Updates the title with the general information provided in the given items, e.g. colour.
    // These items may contain additional lower-level titles which are also updated.
    // If the specified title is empty (default) or not within this collection, it is not 
    // updated, but lower-level titles may be.
    void UpdateTitle(const Parser::ItemSet& items, const std::string& titleID = "");

    std::map<std::string, Title> titles;
};

} // CK2