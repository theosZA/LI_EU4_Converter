#pragma once

#include <set>
#include <string>

#include "Parser.h"

namespace CK2 {

// Represents a CK2 province (which may include multiple holdings).
class Province
{
  public:
    Province(const Parser::Item& provinceItem);

    int GetID() const { return id; }

  private:
    int id;
    std::string name;
    std::string culture;
    std::string religion;
    std::set<std::string> baronyLevelTitles;
};

} // CK2