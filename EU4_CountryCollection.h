#pragma once

#include <map>
#include <string>

#include "EU4_Country.h"
#include "LI_EU4_TitleCountryMapping.h"

namespace CK2 {
class TitleCollection;
} // CK2

namespace EU4 {

// Holds all the countries to be included in the EU4 mod.
class CountryCollection
{
  public:
    // Creates an EU4 collection of countries from the top-level titles
    // in the CK2 title collection. The mapping from CK2 titles to EU4 countries
    // is written to the provided TitleCountryMapping.
    CountryCollection(const CK2::TitleCollection&);

    const Country& GetCountry(const std::string& countryTag) const;
    Country& GetCountry(const std::string& countryTag);

    const Country& GetCountryByTitle(const std::string& titleID) const;
    Country& GetCountryByTitle(const std::string& titleID);
    const Country* GetOptionalCountryByTitle(const std::string& titleID) const;

    // Writes all countries' tags.
    void WriteTags(const std::string& fileName) const;
    // Writes all countries' common information such as colour.
    void WriteCommonInfo(const std::string& path) const;
    // Writes all countries' history including current situation such as current government, religion and rulers.
    void WriteHistory(const std::string& path) const;
    // Writes all countries' name and adjective for localisation.
    void WriteLocalisation(const std::string& fileName) const;

  private:
    LI_EU4::TitleCountryMapping titleCountryMapping;
    std::map<std::string, Country> countries;
};

} // EU4