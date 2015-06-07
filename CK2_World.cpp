#include "CK2_World.h"

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
  for (const auto& fileName : FileUtilities::GetAllFilesInFolder(ck2Path + "\\localisation"))
    localisation.AddLocalisations(std::ifstream(ck2Path + "\\localisation\\" + fileName));

  LOG(LogLevel::Info) << "Reading mod localisations";
  for (const auto& fileName : FileUtilities::GetAllFilesInFolder(modSubPath + "\\localisation"))
    localisation.AddLocalisations(std::ifstream(modSubPath + "\\localisation\\" + fileName));

  LOG(LogLevel::Info) << "Reading mod cultures";
  cultures.reset(new CultureCollection(Parser::Parse(std::ifstream(modSubPath + "\\common\\cultures\\00_cultures.txt"))));

  LOG(LogLevel::Info) << "Reading mod dynasties";
  for (const auto& fileName : FileUtilities::GetAllFilesInFolder(modSubPath + "\\common\\dynasties"))
    dynasties.AddDynasties(Parser::Parse(std::ifstream(modSubPath + "\\common\\dynasties\\" + fileName)));

  LOG(LogLevel::Info) << "Reading save";
  auto saveItems = Parser::Parse(std::ifstream(saveFileName));

  LOG(LogLevel::Info) << "Adding dynasties from save";
  dynasties.AddDynasties(Parser::GetItem(saveItems, "dynasties").items);

  LOG(LogLevel::Info) << "Building source provinces";
  const auto& provinceItem = Parser::GetItem(saveItems, "provinces");
  provinces.reset(new CK2::ProvinceCollection(provinceItem, modSubPath + "\\history\\provinces"));

  LOG(LogLevel::Info) << "Building source characters";
  const auto& charactersItem = Parser::GetItem(saveItems, "character");
  characters.reset(new CK2::CharacterCollection(charactersItem.items));

  LOG(LogLevel::Info) << "Building source titles";
  const auto& titlesItem = Parser::GetItem(saveItems, "title");
  titles.reset(new CK2::TitleCollection(titlesItem, localisation, *provinces));

  LOG(LogLevel::Info) << "Reading LI titles";
  const std::vector<std::string> titlesFileNames { "landed_titles.txt", "mercenary_titles.txt", "religious_titles.txt", "titular_titles.txt" };
  for (const auto& titlesFileName : titlesFileNames)
  {
    std::ifstream titlesFile(modSubPath + "\\common\\landed_titles\\" + titlesFileName);
    titles->UpdateTitles(Parser::Parse(titlesFile));
  }
}

} // CK2