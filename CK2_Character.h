#pragma once

#include <array>
#include <set>
#include <string>

#include "Date.h"

namespace Parser {
struct Item;
} // Parser

namespace EU4 {
class Ruler;
} // EU4

namespace CK2 {

// Represents any character in CK2.
class Character
{
  public:
    Character(const Parser::Item& characterItem);

    int GetID() const { return id; }

    int GetDiplomacy() const;
    int GetStewardship() const;
    int GetMilitary() const;
    int GetIntrigue() const;
    int GetLearning() const;

    const std::string& GetReligion() const { return religion; }
    const std::string& GetCulture() const { return culture; }

    friend class EU4::Ruler;

  private:
    int id;
    std::string birthName;
    int dynasty;

    bool female;
    Date birthDate;
    std::array<int, 5> attributes;
    std::set<int>  traits;
    std::string religion;
    std::string culture;
};

} // CK2