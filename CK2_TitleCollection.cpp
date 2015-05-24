#include "CK2_TitleCollection.h"

#include <iostream>
#include <stdexcept>

namespace CK2 {

// Represents all CK2 landed titles in the game.
TitleCollection::TitleCollection(const Parser::Item& titlesItem)
{
  for (const auto& titleItem : titlesItem.items)
  {
    Title title(*titleItem);
    titles.emplace(title.GetID(), std::move(title));
  }
}

std::string TitleCollection::GetTopLevelLiege(const std::string& titleID) const
{
  std::string highestLiege = titleID;
  bool topLevelReached = false;
  while (!topLevelReached)
  {
    auto findIter = titles.find(highestLiege);
    if (findIter == titles.end())
      throw std::runtime_error("Title " + highestLiege + " not found when determing top-level liege for " + titleID);
    const std::string& newHighestLiege = findIter->second.GetLiege();
    if (newHighestLiege.empty())
      topLevelReached = true;
    else
      highestLiege = newHighestLiege;
  }
  return highestLiege;
}

std::vector<std::string> TitleCollection::GetAllTopLevelTitles() const
{
  std::vector<std::string> topLevelTitles;
  for (const auto& titlePair : titles)
    if (titlePair.second.GetLiege().empty()) // no liege implies this is a top-level title
      topLevelTitles.push_back(titlePair.first);
  return topLevelTitles;
}

} // CK2