#include "EU4_World.h"

#include <fstream>

#include "CK2_World.h"
#include "FileUtilities.h"
#include "LI_EU4_ProvinceMapping.h"
#include "Log.h"

namespace EU4 {

World::World(const CK2::World& source, const std::string& eu4Path)
: cultures(*source.cultures, source.localisation),
  countries(*source.titles),
  provinces(*source.provinces, *source.titles, countries, "province_mapping.txt", eu4Path + "\\history\\provinces")
{}

void World::CreateMod(const std::string& name, const std::string& eu4ModPath, const std::string& ck2ModSubPath)
{
  LOG(LogLevel::Info) << "Creating mod folders";
  std::string convertedModPath = FileUtilities::MakeFolder(eu4ModPath + '\\' + name);
  std::string commonPath = FileUtilities::MakeFolder(convertedModPath + "\\common");
  std::string tagsPath = FileUtilities::MakeFolder(commonPath + "\\country_tags");
  std::string commonCountriesPath = FileUtilities::MakeFolder(commonPath + "\\countries");
  std::string culturesPath = FileUtilities::MakeFolder(commonPath + "\\cultures");
  std::string historyPath = FileUtilities::MakeFolder(convertedModPath + "\\history");
  std::string historyCountriesPath = FileUtilities::MakeFolder(historyPath + "\\countries");
  std::string historyProvincesPath = FileUtilities::MakeFolder(historyPath + "\\provinces");
  std::string localisationPath = FileUtilities::MakeFolder(convertedModPath + "\\localisation");
  std::string graphicsPath = FileUtilities::MakeFolder(convertedModPath + "\\gfx");
  std::string flagsPath = FileUtilities::MakeFolder(graphicsPath + "\\flags");

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
  countries.WriteLocalisation(localisationPath + "\\new_tags_l_english.yml");

  LOG(LogLevel::Info) << "Writing cultures file";
  cultures.WriteToStream(std::ofstream(culturesPath + "\\00_cultures.txt"));

  LOG(LogLevel::Info) << "Writing culture localisations file";
  cultures.WriteLocalisations(std::ofstream(localisationPath + "\\new_cultures_l_english.yml"));

  LOG(LogLevel::Info) << "Writing province files";
  provinces.WriteHistoryToFiles(historyProvincesPath, countries);

  LOG(LogLevel::Info) << "Copying flags";
  auto flagFiles = FileUtilities::GetAllFilesInFolder(ck2ModSubPath + "\\gfx\\flags");
  for (const auto& flagFile : flagFiles)
  {
    auto extPos = flagFile.rfind('.');
    if (extPos != std::string::npos)
    {
      auto title = flagFile.substr(0, extPos);
      auto extension = flagFile.substr(extPos);
      const auto* country = countries.GetOptionalCountryByTitle(title);
      if (country)
        FileUtilities::CopyFile(ck2ModSubPath + "\\gfx\\flags\\" + flagFile, flagsPath + "\\" + country->GetTag() + extension);
    }
  }
}

} // EU4