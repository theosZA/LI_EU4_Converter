#pragma once

#include <istream>
#include <map>
#include <set>
#include <vector>

namespace LI_EU4 {

// Holds a mapping between LI provinces and EU4 provinces
class ProvinceMapping
{
  public:
    // Creates a mapping from key-value pairs in the given stream.
    ProvinceMapping(std::istream&);

    std::set<int> GetAllEU4ProvinceIDs() const;

  private:
    // Mapping is from EU4 province IDs to the LI province IDs which constitute each EU4 province.
    std::map<int, std::vector<int>> mapping;
};

} // LI_EU4