#pragma once

#include <map>
#include <string>

#include "CK2_Province.h"
#include "Parser.h"

namespace CK2 {

class TitleCollection;

// Represents all CK2 provinces on the map.
class ProvinceCollection
{
  public:
    ProvinceCollection(const Parser::Item& provincesItem, const std::string& historyProvincesPath);

    const Province& GetProvince(int provinceID) const;

    // Returns the ID for the province which has the specified title ID as its county-level title.
    // Returns -1 if no matching province was found.
    int GetProvinceIDForCountyLevelTitle(const std::string& titleID) const;

  private:
    std::map<int, Province> provinces;
};

} // CK2