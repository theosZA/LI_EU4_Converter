#pragma once

#include <memory>
#include <string>

#include "CK2_World.h"
#include "EU4_CountryCollection.h"
#include "EU4_ProvinceCollection.h"
#include "LI_EU4_ProvinceMapping.h"

namespace EU4 {

// Represents everything to be written out in the EU4 mod.
class World
{
  public:
    // Creates an EU4 world from a CK2 world using the given CK2-EU4 province mapping.
    // The vanilla world in the EU4 path is used as the baseline.
    World(const CK2::World&, const std::string& eu4Path, const LI_EU4::ProvinceMapping&);

    // Writes this world as an EU4 mod (to your EU4 mod path).
    void CreateMod(const std::string& name, const std::string& eu4ModPath);

  private:
    std::unique_ptr<CountryCollection> countries;
    std::unique_ptr<ProvinceCollection> provinces;
};

} // EU4