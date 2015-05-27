#pragma once

#include <memory>
#include <string>

#include "CK2_World.h"
#include "EU4_World.h"

namespace LI_EU4 {

// Holds the full state of both the pre-converted CK2 world (save + LI mod)
// and the post-converted EU4 world (mod).
class World
{
  public:
    // Creates a CK2 world and then converts it to an EU4 world.
    World(const std::string& ck2SaveFileName,
          const std::string& liModPath,
          const std::string& eu4Path);

    // Writes the converted EU4 world as an EU4 mod (to your EU4 mod path).
    void CreateMod(const std::string& name, const std::string& eu4ModPath);
    
  private:
    std::unique_ptr<CK2::World> source;
    std::unique_ptr<EU4::World> dest;
};

} // LI_EU4