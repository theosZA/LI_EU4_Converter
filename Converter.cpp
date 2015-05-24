#include "Converter.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "EU4_CountryCollection.h"
#include "EU4_ProvinceCollection.h"
#include "FileUtilities.h"
#include "LI_EU4_ProvinceMapping.h"
#include "LI_EU4_TitleCountryMapping.h"
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

  std::cout << "Reading province mapping\n";
  LI_EU4::ProvinceMapping provinceMapping(std::ifstream("province_mapping.txt"));
  
  std::cout << "Reading EU4 provinces\n";
  EU4::ProvinceCollection destProvinces(provinceMapping.GetAllEU4ProvinceIDs(), eu4Path + "\\history\\provinces");

  std::cout << "Creating EU4 countries\n";
  EU4::CountryCollection countries;
  LI_EU4::TitleCountryMapping countryMapping(*sourceTitles, countries);

  std::cout << "Converting provinces to EU4\n";
  provinceMapping.ConvertProvinces(*sourceProvinces, *sourceTitles, countryMapping, destProvinces);

  std::cout << "Creating mod folders\n";
  std::string convertedModPath = MakeFolder(modPath + '\\' + name);
  std::string commonPath = MakeFolder(convertedModPath + "\\common");
  std::string tagsPath = MakeFolder(commonPath + "\\country_tags");
  std::string commonCountriesPath = MakeFolder(commonPath + "\\countries");
  std::string historyPath = MakeFolder(convertedModPath + "\\history");
  std::string historyCountriesPath = MakeFolder(historyPath + "\\countries");
  std::string historyProvincesPath = MakeFolder(historyPath + "\\provinces");
  std::string localisationPath = MakeFolder(convertedModPath + "\\localisation");

  std::cout << "Writing mod file\n";
  {
    std::ofstream modFile(modPath + '\\' + name + ".mod");
    modFile << "name=\"" << name << "\"\n"
            << "path=\"mod/" << name << "\"\n"
            << "disable_time_widget = yes\n"
            << "supported_version = 1.11\n";
  }

  std::cout << "Writing country tags file\n";
  countries.WriteTags(tagsPath + "\\01_country_tags.txt");

  std::cout << "Writing country common info files\n";
  countries.WriteCommonInfo(commonCountriesPath);

  std::cout << "Writing country history files\n";
  countries.WriteHistory(historyCountriesPath);

  std::cout << "Writing country localisations file\n";
  countries.WriteLocalisation(localisationPath + '\\' + name + "_tags_l_english.yml");

  std::cout << "Writing province files\n";
  destProvinces.WriteHistoryToFiles(historyProvincesPath, countries);
}