#pragma once

#include <istream>
#include <map>
#include <set>
#include <vector>

namespace CK2 { 
  class ProvinceCollection; 
  class TitleCollection;
} // CK2

namespace EU4 { 
  class ProvinceCollection; 
} // EU4

namespace LI_EU4 {

class TitleCountryMapping;

// Holds a mapping between LI provinces and EU4 provinces
class ProvinceMapping
{
  public:
    // Creates a mapping from key-value pairs in the given stream.
    ProvinceMapping(std::istream&);

    std::set<int> GetAllEU4ProvinceIDs() const;

    // Converts all CK2 provinces provided into EU4 provinces.
    void ConvertProvinces(const CK2::ProvinceCollection&, const CK2::TitleCollection&, const TitleCountryMapping&, EU4::ProvinceCollection&) const;

  private:
    // Mapping is from EU4 province IDs to the LI province IDs which constitute each EU4 province.
    std::map<int, std::vector<int>> mapping;
};

} // LI_EU4