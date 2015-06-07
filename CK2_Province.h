#pragma once

#include <string>
#include <vector>

#include "Parser.h"

namespace CK2 {

class CharacterCollection;
class TitleCollection;

// Represents a CK2 province (which may include multiple holdings).
class Province
{
  public:
    Province(const Parser::Item& provinceItem);

    // Updates this province with the immutable history from the given items.
    void UpdateFromHistory(const Parser::ItemSet& historyItems);

    int GetID() const { return id; }
    const std::string& GetName() const { return name; }
    const std::string& GetCulture() const { return culture; }

    std::string GetTopLevelTitle(const TitleCollection&, const CharacterCollection&) const;
    const std::string& GetCountyLevelTitleID() const { return countyLevelTitleID; }

  private:
    int id;
    std::string name;
    std::string culture;
    std::string religion;
    std::string countyLevelTitleID;
    std::vector<std::string> baronyLevelTitles;
};

} // CK2