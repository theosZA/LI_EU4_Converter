#include "CK2_Province.h"

#include "CK2_TitleCollection.h"

#include "StringUtilities.h"
#include "Unicode.h"

namespace CK2 {

Province::Province(const Parser::Item& provinceItem)
: id(std::stoi(provinceItem.key))
{
  for (const auto& provinceSubItem : provinceItem.items)
  {
    if (provinceSubItem->key == "name")
      name = Unicode::Windows1252ToUTF8(StripQuotes(provinceSubItem->value));
    else if (provinceSubItem->key == "culture")
      culture = provinceSubItem->value;
    else if (provinceSubItem->key == "religion")
      religion = provinceSubItem->value;
    else if (provinceSubItem->key.size() >= 2 && provinceSubItem->key[0] == 'b' && provinceSubItem->key[1] == '_')
      baronyLevelTitles.push_back(provinceSubItem->key);
  }
}

void Province::UpdateFromHistory(const Parser::ItemSet& historyItems)
{
  for (const auto& historyItem : historyItems)
    if (historyItem->key == "title")
      countyLevelTitleID = historyItem->value;
}

std::string Province::GetTopLevelTitle(const TitleCollection& titles) const
{
  if (baronyLevelTitles.empty())
    return "";

  return titles.GetTopLevelLiege(baronyLevelTitles.front());
}

} // CK2