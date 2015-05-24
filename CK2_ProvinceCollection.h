#pragma once

#include <map>

#include "CK2_Province.h"
#include "Parser.h"

namespace CK2 {

class TitleCollection;

// Represents all CK2 provinces on the map.
class ProvinceCollection
{
  public:
    ProvinceCollection(const Parser::Item& provincesItem);

    // Returns the top-level title holder over the specified province, i.e. who the
    // province effectively belongs to in a normal map-mode.
    std::string GetProvinceTopLevelTitle(int provinceID, const TitleCollection&) const;

  private:
    std::map<int, Province> provinces;
};

} // CK2