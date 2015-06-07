#pragma once

#include <map>

#include "CK2_Dynasty.h"
#include "Parser.h"

namespace CK2 {

// Represents all dynasties in CK2.
class DynastyCollection
{
  public:
    void AddDynasties(const Parser::ItemSet& dynastyItems);

    const Dynasty& GetDynasty(int id) const;

  private:
    std::map<int, Dynasty> dynasties;
};

} // CK2