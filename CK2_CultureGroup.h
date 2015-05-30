#pragma once

#include <map>

#include "CK2_Culture.h"

namespace EU4 {
class CultureGroup;
} // EU4

namespace CK2 {

// A culture group is a linked set of cultures.
class CultureGroup
{
  public:
    CultureGroup(const Parser::Item&);

    friend EU4::CultureGroup;

  private:
    std::string id;
    std::string portraitGraphicalCulture;
    std::string unitGraphicalCulture;
    std::map<std::string, Culture> cultures;
};

} // CK2