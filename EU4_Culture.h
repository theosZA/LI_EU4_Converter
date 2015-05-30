#pragma once

#include <ostream>
#include <string>
#include <vector>

#include "Parser.h"

namespace CK2 {
class Culture;
class Localisation;
} // CK2

namespace EU4 {

class Culture
{
  public:
    Culture(const CK2::Culture&, const CK2::Localisation&);

    void WriteToStream(std::ostream&) const;
    void WriteLocalisation(std::ostream&) const;

  private:
    std::string id;
    std::string name;
    std::string graphicalCulture;
    std::vector<std::string> maleNames;
    std::vector<std::string> femaleNames;
};

} // EU4