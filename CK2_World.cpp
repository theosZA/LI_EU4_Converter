#include "CK2_World.h"

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "FileUtilities.h"
#include "Log.h"
#include "Parser.h"

namespace CK2 {

World::World(const std::string& ck2Path, const std::string& saveFileName, const std::string& modSubPath)
{
  LOG(LogLevel::Info) << "Reading vanilla localisations";
  for (const auto& fileName : GetAllFilesInFolder(ck2Path + "\\localisation"))
    localisation.AddLocalisations(std::ifstream(ck2Path + "\\localisation\\" + fileName));

  LOG(LogLevel::Info) << "Reading mod localisations";
  for (const auto& fileName : GetAllFilesInFolder(modSubPath + "\\localisation"))
    localisation.AddLocalisations(std::ifstream(modSubPath + "\\localisation\\" + fileName));

  LOG(LogLevel::Info) << "Reading save";
  auto saveItems = Parser::Parse(std::ifstream(saveFileName));

  LOG(LogLevel::Info) << "Building source provinces";
  auto provinceItem = std::find_if(saveItems.begin(), saveItems.end(), [](const std::unique_ptr<Parser::Item>& item) { return item->key == "provinces"; });
  if (provinceItem == saveItems.end())
    throw std::runtime_error("Failed to find provinces entry in save game file");
  provinces.reset(new CK2::ProvinceCollection(**provinceItem));

  LOG(LogLevel::Info) << "Building source titles";
  auto titleItem = std::find_if(saveItems.begin(), saveItems.end(), [](const std::unique_ptr<Parser::Item>& item) { return item->key == "title"; });
  if (titleItem == saveItems.end())
    throw std::runtime_error("Failed to find title entry in save game file");
  titles.reset(new CK2::TitleCollection(**titleItem, localisation));

  LOG(LogLevel::Info) << "Reading LI titles";
  const std::vector<std::string> titlesFileNames { "landed_titles.txt", "mercenary_titles.txt", "religious_titles.txt", "titular_titles.txt" };
  for (const auto& titlesFileName : titlesFileNames)
  {
    std::ifstream titlesFile(modSubPath + "\\common\\landed_titles\\" + titlesFileName);
    titles->UpdateTitles(Parser::Parse(titlesFile));
  }
}

} // CK2