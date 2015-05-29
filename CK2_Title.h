#pragma once

#include <string>

#include "Colour.h"
#include "Parser.h"

namespace EU4 {
class Country;
} // EU4

namespace CK2 {

class Localisation;

// Represents a CK2 landed title from baronies to empires.
class Title
{
  public:
    Title(const Parser::Item& titleItem, const Localisation&);

    const std::string& GetID() const { return id; }
    const std::string& GetLiege() const { return liegeTitle; }

    void SetColour(Colour newColour) { colour = newColour; }

    friend EU4::Country;

  private:
    std::string id;
    std::string name;
    std::string adjective;
    int holderID; // This is the character who directly holds this title.
    std::string liegeTitle;  // The title under which this title falls. Empty if this is a top-level title.
    std::string succession;
    Colour colour;
};

} // CK2