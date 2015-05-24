#pragma once

#include <map>
#include <string>

namespace CK2 {
class TitleCollection;
} // CK2

namespace EU4 {
class CountryCollection;
} // EU4

namespace LI_EU4 {

// Holds a mapping from CK2 (top-level) titles to EU4 countries.
class TitleCountryMapping 
{
  public:
    // Creates new countries from the top-level titles, adding them to the EU4
    // country collection and this mapping.
    TitleCountryMapping(const CK2::TitleCollection&, EU4::CountryCollection&);

    // Returns the EU4 country corresponding the given CK2 (top-level) title.
    const std::string& GetCountryTag(const std::string& titleID) const;

  private:
    std::map<std::string, std::string> mapping; // CK2 title ID to EU4 country tag
};

} // LI_EU4