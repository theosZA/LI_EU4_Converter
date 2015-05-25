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

void TitleCollection::UpdateTitles(const Parser::ItemSet& items)
{
  UpdateTitle(items);
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

const Title& TitleCollection::GetTitle(const std::string& titleID) const
{
  auto findIter = titles.find(titleID);
  if (findIter == titles.end())
    throw std::runtime_error("Title " + titleID + " not found");
  return findIter->second;
}

void TitleCollection::UpdateTitle(const Parser::ItemSet& items, const std::string& titleID)
{
  Title* title = nullptr;
  if (!titleID.empty())
  {
    auto findIter = titles.find(titleID);
    if (findIter != titles.end())
      title = &findIter->second;
  }

  for (const auto& item : items)
  {
    if (title)
    {
      if (item->key == "color")
      {
        const auto& colourItems = item->items;
        if (!colourItems.empty())
          title->SetColour(colourItems.front()->key);
      }
    }
    if (item->key.size() >= 2 && item->key[1] == '_') // matches a title, e.g. k_england
      UpdateTitle(item->items, item->key);
  }
}

} // CK2