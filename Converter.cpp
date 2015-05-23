#include "Converter.h"

#include <direct.h>
#include <fstream>
#include <stdexcept>

#include "EU4_Country.h"
#include "EU4_Province.h"

const std::string& MakeFolder(const std::string& newPath)
{
  _mkdir(newPath.c_str());
  return newPath;
}

void Converter::CreateMod(const std::string& name, const std::string& modPath, const std::string& eu4Path)
{
  std::string convertedModPath = MakeFolder(modPath + '\\' + name);
  std::string commonPath = MakeFolder(convertedModPath + "\\common");
  std::string tagsPath = MakeFolder(commonPath + "\\country_tags");
  std::string commonCountriesPath = MakeFolder(commonPath + "\\countries");
  std::string historyPath = MakeFolder(convertedModPath + "\\history");
  std::string historyCountriesPath = MakeFolder(historyPath + "\\countries");
  std::string historyProvincesPath = MakeFolder(historyPath + "\\provinces");
  std::string localisationPath = MakeFolder(convertedModPath + "\\localisation");

  EU4::Country testCountry;

  {
    std::ofstream modFile(modPath + '\\' + name + ".mod");
    modFile << "name=\"" << name << "\"\n"
            << "path=\"mod/" << name << "\"\n"
            << "disable_time_widget = yes\n"
            << "supported_version = 1.11\n";
  }

  {
    std::ofstream tagsFile(tagsPath + "\\01_country_tags.txt");
    if (!tagsFile)
      throw std::runtime_error("Error creating tags file");
    tagsFile << testCountry.GetTag() << " = " << "countries/" << testCountry.GetName() << ".txt\n";
  }

  {
    std::ofstream commonFile(commonCountriesPath + '\\' + testCountry.GetName() + ".txt");
    if (!commonFile)
      throw std::runtime_error("Error creating common country file for country " + testCountry.GetName());
    testCountry.WriteCommonInfo(commonFile);
  }

  {
    std::ofstream historyFile(historyCountriesPath + '\\' + testCountry.GetTag() + " - " + testCountry.GetName() + ".txt");
    if (!historyFile)
      throw std::runtime_error("Error creating common history file for country " + testCountry.GetName());
    testCountry.WriteHistory(historyFile);
  }

  {
    std::ofstream localisationCountriesFile(localisationPath + '\\' + name + "_tags_l_english.yml");
    if (!localisationCountriesFile)
      throw std::runtime_error("Error creating countries localistion file");
    localisationCountriesFile << "l_english:\n";
    testCountry.WriteLocalisation(localisationCountriesFile);
  }

  std::ifstream sjaellandSourceFile(eu4Path + "\\history\\provinces\\12-Sjaelland.txt");
  EU4::Province sjaelland(12, "Sjaelland", sjaellandSourceFile);
  sjaelland.ResetOwner(testCountry.GetTag());

  {
    std::ofstream provinceFile(historyProvincesPath + '\\' + std::to_string(sjaelland.GetID()) + '-' + sjaelland.GetName() + ".txt");
    sjaelland.WriteHistory(provinceFile,
        [&](const std::string& tag)
        { // Only 1 country so need to check the tag.
          return testCountry.GetName(); 
        });
  }
}