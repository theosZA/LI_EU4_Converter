#pragma once

#include <istream>
#include <map>
#include <set>
#include <vector>

namespace LI_EU4 {

// Holds a mapping between CK2 provinces and EU4 provinces
class ProvinceMapping
{
  public:
    // Creates a mapping from key-value pairs in the given stream.
    ProvinceMapping(std::istream&);

    // Returns the IDs of all EU4 provinces mapped to from CK2 provinces.
    std::set<int> GetAllEU4SettledProvinceIDs() const;
    // Returns the IDs of all EU4 provinces that are explicitly designated as empty provinces.
    std::set<int> GetAllEU4EmptyProvinceIDs() const;
    // Returns all CK2 provinces that map to the given EU4 province.
    const std::vector<int>& GetCK2ProvinceIDs(int eu4ProvinceID) const;

  private:
    // Mapping is from EU4 province IDs to the LI province IDs which constitute each EU4 province.
    std::map<int, std::vector<int>> mapping;
};

} // LI_EU4