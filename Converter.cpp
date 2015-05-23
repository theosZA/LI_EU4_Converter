#include "Converter.h"

#include <direct.h>
#include <fstream>
#include <stdexcept>

#include "EU4_Country.h"

const std::string& MakeFolder(const std::string& newPath)
{
  _mkdir(newPath.c_str());
  return newPath;
}

void Converter::CreateMod(const std::string& name, const std::string& modPath)
{
  std::string convertedModPath = MakeFolder(modPath + '\\' + name);
  std::string commonPath = MakeFolder(convertedModPath + "\\common");
  std::string tagsPath = MakeFolder(commonPath + "\\country_tags");
  std::string commonCountriesPath = MakeFolder(commonPath + "\\countries");
  std::string historyPath = MakeFolder(convertedModPath + "\\history");
  std::string historyCountriesPath = MakeFolder(historyPath + "\\countries");
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

  // Force this country to show up in Uppland
  {
    std::string historyProvincesPath = MakeFolder(historyPath + "\\provinces");
    std::ofstream provinceFile(historyProvincesPath + "\\1-Uppland.txt");
    provinceFile << "#Uppland, contains Stockholm, Uppsala & Nyköping.\n\n"
                 << "owner = " << testCountry.GetTag() << " # " << testCountry.GetName() << '\n'
                 << "controller = " << testCountry.GetTag() << " # " << testCountry.GetName() << '\n'
                 << "add_core = " << testCountry.GetTag() << " # " << testCountry.GetName() << '\n'
                 << "culture = swedish\n"
                 << "religion = catholic\n"
                 << "hre = no\n"
                 << "base_tax = 5\n"
                 << "trade_goods = grain\n"
                 << "manpower = 3\n"
                 << "fort1 = yes\n"
                 << "capital = \"Stockholm\"\n"
                 << "is_city = yes\n"
                 << "temple = yes\n"
                 << "workshop = yes\n"
                 << "marketplace = yes\n"
                 << "discovered_by = eastern\n"
                 << "discovered_by = western\n"
                 << "discovered_by = muslim\n"
                 << "discovered_by = ottoman\n";
  }
}