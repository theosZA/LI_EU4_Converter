#pragma once

#include <map>
#include <string>

#include "EU4_Country.h"

namespace EU4 {

// Holds all the countries to be included in the EU4 mod.
class CountryCollection
{
  public:
    void AddCountry(Country&&);

    const Country& GetCountry(const std::string& countryTag) const;
    Country& GetCountry(const std::string& countryTag);

    // Writes all countries' tags.
    void WriteTags(const std::string& fileName) const;
    // Writes all countries' common information such as colour.
    void WriteCommonInfo(const std::string& path) const;
    // Writes all countries' history including current situation such as current government, religion and rulers.
    void WriteHistory(const std::string& path) const;
    // Writes all countries' name and adjective for localisation.
    void WriteLocalisation(const std::string& fileName) const;

  private:
    std::map<std::string, Country> countries;
};

} // EU4