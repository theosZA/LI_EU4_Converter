#include "LI_EU4_World.h"

#include <fstream>

#include "LI_EU4_ProvinceMapping.h"
#include "LI_EU4_TitleCountryMapping.h"
#include "Log.h"

namespace LI_EU4 {

World::World(const std::string& ck2SaveFileName,
             const std::string& liModPath,
             const std::string& eu4Path)
{
  source.reset(new CK2::World(ck2SaveFileName, liModPath));

  LOG(LogLevel::Info) << "Reading province mapping";
  ProvinceMapping provinceMapping(std::ifstream("province_mapping.txt"));

  dest.reset(new EU4::World(*source, eu4Path, provinceMapping));
}

void World::CreateMod(const std::string& name, const std::string& eu4ModPath)
{
  dest->CreateMod(name, eu4ModPath);
}


} // LI_EU4