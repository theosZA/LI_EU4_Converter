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

    // Returns the name of the specified province.
    const std::string& GetProvinceName(int provinceID) const;

    // Returns the top-level title holder over the specified province, i.e. who the
    // province effectively belongs to in a normal map-mode.
    std::string GetProvinceTopLevelTitle(int provinceID, const TitleCollection&) const;

    // Returns the ID for the province which has the specified title ID as its county-level title.
    // Returns -1 if no matching province was found.
    int GetProvinceIDForCountyLevelTitle(const std::string& titleID) const;

  private:
    std::map<int, Province> provinces;
};

} // CK2