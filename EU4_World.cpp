#include "EU4_World.h"

#include <fstream>

#include "CK2_World.h"
#include "FileUtilities.h"
#include "LI_EU4_ProvinceMapping.h"
#include "Log.h"

namespace EU4 {

World::World(const CK2::World& source, const std::string& eu4Path)
: countries(*source.titles),
  provinces(*source.provinces, *source.titles, countries, "province_mapping.txt", eu4Path + "\\history\\provinces")
{}

void World::CreateMod(const std::string& name, const std::string& eu4ModPath)
{
  LOG(LogLevel::Info) << "Creating mod folders";
  std::string convertedModPath = MakeFolder(eu4ModPath + '\\' + name);
  std::string commonPath = MakeFolder(convertedModPath + "\\common");
  std::string tagsPath = MakeFolder(commonPath + "\\country_tags");
  std::string commonCountriesPath = MakeFolder(commonPath + "\\countries");
  std::string historyPath = MakeFolder(convertedModPath + "\\history");
  std::string historyCountriesPath = MakeFolder(historyPath + "\\countries");
  std::string historyProvincesPath = MakeFolder(historyPath + "\\provinces");
  std::string localisationPath = MakeFolder(convertedModPath + "\\localisation");

  LOG(LogLevel::Info) << "Writing mod file";
  {
    std::ofstream modFile(eu4ModPath + '\\' + name + ".mod");
    modFile << "name=\"" << name << "\"\n"
            << "path=\"mod/" << name << "\"\n"
            << "disable_time_widget = yes\n"
            << "supported_version = 1.11\n";
  }

  LOG(LogLevel::Info) << "Writing country tags file";
  countries.WriteTags(tagsPath + "\\01_country_tags.txt");

  LOG(LogLevel::Info) << "Writing country common info files";
  countries.WriteCommonInfo(commonCountriesPath);

  LOG(LogLevel::Info) << "Writing country history files";
  countries.WriteHistory(historyCountriesPath);

  LOG(LogLevel::Info) << "Writing country localisations file";
  countries.WriteLocalisation(localisationPath + '\\' + name + "_tags_l_english.yml");

  LOG(LogLevel::Info) << "Writing province files";
  provinces.WriteHistoryToFiles(historyProvincesPath, countries);
}

} // EU4