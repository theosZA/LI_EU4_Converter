#pragma once

#include <memory>
#include <string>

#include "CK2_ProvinceCollection.h"
#include "CK2_TitleCollection.h"

namespace EU4 {
class World;
} // EU4

namespace CK2 {

// Represents everything relevant in the CK2 mod and save.
class World
{
  public:
    // Constructor from a save game and the mod in the given path.
    World(const std::string& saveFileName, const std::string& modSubPath);

    friend EU4::World;

  private:
    std::unique_ptr<CK2::ProvinceCollection> provinces;
    std::unique_ptr<CK2::TitleCollection> titles;
};

} // CK2