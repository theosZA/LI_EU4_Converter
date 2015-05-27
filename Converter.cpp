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
#include "Log.h"
#include "Parser.h"

void Converter::ReadSave(const std::string& saveFileName, const std::string& liModPath)
{
  LOG(LogLevel::Info) << "Reading save";
  auto saveItems = Parser::Parse(std::ifstream(saveFileName));

  LOG(LogLevel::Info) << "Building source provinces";
  auto provinceItem = std::find_if(saveItems.begin(), saveItems.end(), [](const std::unique_ptr<Parser::Item>& item) { return item->key == "provinces"; });
  if (provinceItem == saveItems.end())
    throw std::runtime_error("Failed to find provinces entry in save game file");
  sourceProvinces.reset(new CK2::ProvinceCollection(**provinceItem));

  LOG(LogLevel::Info) << "Building source titles";
  auto titleItem = std::find_if(saveItems.begin(), saveItems.end(), [](const std::unique_ptr<Parser::Item>& item) { return item->key == "title"; });
  if (titleItem == saveItems.end())
    throw std::runtime_error("Failed to find title entry in save game file");
  sourceTitles.reset(new CK2::TitleCollection(**titleItem));

  LOG(LogLevel::Info) << "Reading LI titles";
  const std::vector<std::string> titlesFileNames { "landed_titles.txt", "mercenary_titles.txt", "religious_titles.txt", "titular_titles.txt" };
  for (const auto& titlesFileName : titlesFileNames)
  {
    std::ifstream titlesFile(liModPath + "\\common\\landed_titles\\" + titlesFileName);
    sourceTitles->UpdateTitles(Parser::Parse(titlesFile));
  }
}

void Converter::CreateMod(const std::string& name, const std::string& eu4ModPath, const std::string& eu4Path)
{
  LOG(LogLevel::Info) << "Creating mod";

  LOG(LogLevel::Info) << "Reading province mapping";
  LI_EU4::ProvinceMapping provinceMapping(std::ifstream("province_mapping.txt"));
  
  LOG(LogLevel::Info) << "Reading EU4 provinces";
  EU4::ProvinceCollection destProvinces(provinceMapping.GetAllEU4ProvinceIDs(), eu4Path + "\\history\\provinces");

  LOG(LogLevel::Info) << "Creating EU4 countries";
  EU4::CountryCollection countries;
  LI_EU4::TitleCountryMapping countryMapping(*sourceTitles, countries);

  LOG(LogLevel::Info) << "Converting provinces to EU4";
  provinceMapping.ConvertProvinces(*sourceProvinces, *sourceTitles, countryMapping, destProvinces);

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
  destProvinces.WriteHistoryToFiles(historyProvincesPath, countries);
}