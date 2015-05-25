#pragma once

#include <string>

#include "Colour.h"
#include "Parser.h"

namespace CK2 {

// Represents a CK2 landed title from baronies to empires.
class Title
{
  public:
    Title(const Parser::Item& titleItem);

    const std::string& GetID() const { return id; }
    const std::string& GetLiege() const { return liegeTitle; }
    const Colour& GetColour() const { return colour; }

    void SetColour(Colour newColour) { colour = newColour; }

  private:
    std::string id;
    int holderID; // This is the character who directly holds this title.
    std::string liegeTitle;  // The title under which this title falls. Empty if this is a top-level title.
    std::string succession;
    Colour colour;
};

} // CK2