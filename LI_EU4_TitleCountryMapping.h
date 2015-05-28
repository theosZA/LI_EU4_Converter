#pragma once

#include <map>
#include <string>

namespace LI_EU4 {

// Holds a mapping from CK2 (top-level) titles to EU4 countries.
class TitleCountryMapping 
{
  public:
    TitleCountryMapping();

    // Creates a new country tag from the specified title ID and adds it
    // to the mapping. Returns the new country tag.
    std::string AddTitleAsNewCountry(const std::string& titleID);

    // Returns the EU4 country corresponding the given CK2 (top-level) title.
    const std::string& GetCountryTag(const std::string& titleID) const;

  private:
    std::string lastTag;
    std::map<std::string, std::string> mapping; // CK2 title ID to EU4 country tag
};

} // LI_EU4