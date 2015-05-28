#pragma once

#include <string>

#include "EU4_CountryCollection.h"
#include "EU4_ProvinceCollection.h"

namespace CK2 {
class World;
} // CK2

namespace EU4 {

// Represents everything to be written out in the EU4 mod.
class World
{
  public:
    // Creates an EU4 world from a CK2 world. The vanilla world in the EU4 path is used as the baseline.
    World(const CK2::World&, const std::string& eu4Path);

    // Writes this world as an EU4 mod (to your EU4 mod path).
    void CreateMod(const std::string& name, const std::string& eu4ModPath);

  private:
    CountryCollection countries;
    ProvinceCollection provinces;
};

} // EU4