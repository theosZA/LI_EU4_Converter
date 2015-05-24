#include "Converter.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "EU4_Country.h"
#include "EU4_ProvinceCollection.h"
#include "FileUtilities.h"
#include "LI_EU4_ProvinceMapping.h"
#include "Parser.h"

void Converter::ReadSave(const std::string& saveFileName)
{
  std::cout << "Reading save\n";
  auto saveItems = Parser::Parse(std::ifstream(saveFileName));
  std::cout << "Building source provinces\n";
  auto provinceItem = std::find_if(saveItems.begin(), saveItems.end(), [](const std::unique_ptr<Parser::Item>& item) { return item->key == "provinces"; });
  if (provinceItem == saveItems.end())
    throw std::runtime_error("Failed to find provinces entry in save game file");
  sourceProvinces.reset(new CK2::ProvinceCollection(**provinceItem));
  std::cout << "Building source titles\n";
  auto titleItem = std::find_if(saveItems.begin(), saveItems.end(), [](const std::unique_ptr<Parser::Item>& item) { return item->key == "title"; });
  if (titleItem == saveItems.end())
    throw std::runtime_error("Failed to find title entry in save game file");
  sourceTitles.reset(new CK2::TitleCollection(**titleItem));
}

void Converter::CreateMod(const std::string& name, const std::string& modPath, const std::string& eu4Path)
{
  std::cout << "Creating mod\n";

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

  LI_EU4::ProvinceMapping provinceMapping(std::ifstream("province_mapping.txt"));
  EU4::ProvinceCollection provinces(provinceMapping.GetAllEU4ProvinceIDs(), eu4Path + "\\history\\provinces");

  provinces.ResetOwnerForAllProvinces(testCountry.GetTag());
  provinces.WriteHistoryToFiles(historyProvincesPath,
      [&](const std::string& tag)
      { // Only 1 country so need to check the tag.
        return testCountry.GetName(); 
      });
}