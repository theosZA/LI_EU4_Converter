#pragma once

#include <map>
#include <string>

#include "CK2_CultureGroup.h"
#include "Parser.h"

namespace EU4 {
class CultureCollection;
}

namespace CK2 {

// Holds all culture groups and their specific cultures.
class CultureCollection
{
  public:
    CultureCollection(const Parser::ItemSet&);

    friend EU4::CultureCollection;

  private:
    std::map<std::string, CultureGroup> cultureGroups;
};

} // CK2