#pragma once

#include <string>
#include <vector>

#include "Colour.h"
#include "Parser.h"

namespace EU4 {
class Culture;
} // EU4

namespace CK2 {

class Culture
{
  public:
    Culture(const Parser::Item&, const std::string& groupPortraitGraphicalCulture, const std::string& groupUnitGraphicalCulture);

    friend EU4::Culture;

  private:
    std::string id;
    std::string portraitGraphicalCulture;
    std::string unitGraphicalCulture;
    Colour colour;
    std::vector<std::string> maleNames;
    std::vector<std::string> femaleNames;
};

} // CK2