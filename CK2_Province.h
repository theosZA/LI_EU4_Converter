#pragma once

#include <string>
#include <vector>

#include "Parser.h"

namespace CK2 {

class TitleCollection;

// Represents a CK2 province (which may include multiple holdings).
class Province
{
  public:
    Province(const Parser::Item& provinceItem);

    int GetID() const { return id; }

    std::string GetTopLevelTitle(const TitleCollection&) const;

  private:
    int id;
    std::string name;
    std::string culture;
    std::string religion;
    std::vector<std::string> baronyLevelTitles;
};

} // CK2