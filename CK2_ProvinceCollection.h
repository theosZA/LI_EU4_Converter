#pragma once

#include <map>

#include "CK2_Province.h"
#include "Parser.h"

namespace CK2 {

// Represents all CK2 provinces on the map.
class ProvinceCollection
{
  public:
    ProvinceCollection(const Parser::Item& provincesItem);

  private:
    std::map<int, Province> provinces;
};

} // CK2