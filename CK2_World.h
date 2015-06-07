#pragma once

#include <memory>
#include <string>

#include "CK2_CharacterCollection.h"
#include "CK2_CultureCollection.h"
#include "CK2_Localisation.h"
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
    World(const std::string& ck2Path, const std::string& saveFileName, const std::string& modSubPath);

    friend EU4::World;

  private:
    Localisation localisation;
    std::unique_ptr<CharacterCollection> characters;
    std::unique_ptr<CultureCollection> cultures;
    std::unique_ptr<ProvinceCollection> provinces;
    std::unique_ptr<TitleCollection> titles;
};

} // CK2