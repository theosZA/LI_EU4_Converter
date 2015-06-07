#pragma once

#include <array>
#include <set>
#include <string>

#include "Date.h"

namespace Parser {
struct Item;
} // Parser

namespace EU4 {
class Country;
class Ruler;
} // EU4

namespace CK2 {

// Represents any character in CK2.
class Character
{
  public:
    Character(const Parser::Item& characterItem);

    int GetID() const { return id; }

    const std::string& GetPrimaryTitle() const { return primaryTitle; }

    int GetDiplomacy() const;
    int GetStewardship() const;
    int GetMilitary() const;
    int GetIntrigue() const;
    int GetLearning() const;

    friend class EU4::Country;
    friend class EU4::Ruler;

  private:
    int id;
    std::string birthName;
    int dynasty;

    std::string primaryTitle;
    std::string capitalHolding;

    bool female;
    Date birthDate;
    std::array<int, 5> attributes;
    std::set<int>  traits;
    std::string religion;
    std::string culture;
};

} // CK2