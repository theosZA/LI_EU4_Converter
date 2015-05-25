#include "LI_EU4_TitleCountryMapping.h"

#include <stdexcept>

#include "CK2_TitleCollection.h"
#include "EU4_CountryCollection.h"

namespace LI_EU4 {

// Increases tags where the last letter is a digit, the others are letters.
void IncrementTag(std::string& tag)
{
  ++tag[2];
  if (tag[2] <= '9')
    return;
  tag[2] = '0';
  ++tag[1];
  if (tag[1] <= 'Z')
    return;
  tag[1]= 'A';
  ++tag[0];
  if (tag[0] <= 'Z')
    return;

  throw std::runtime_error("Out of tags");
}

TitleCountryMapping::TitleCountryMapping(const CK2::TitleCollection& titles, EU4::CountryCollection& countries)
{
  // Create tags GA0 through ZZ9 (5200 tags)
  std::string tag = "FZ9";
  
  auto topLevelTitles = titles.GetAllTopLevelTitles();
  for (const auto& titleID : topLevelTitles)
  {
    const auto& title = titles.GetTitle(titleID);
    IncrementTag(tag);
    EU4::Country country(tag, titleID, titleID, title.GetColour());  // TBD: name and adjective of title, not the ID itself
    mapping.emplace(titleID, tag);
    countries.AddCountry(std::move(country));
  }
}

const std::string& TitleCountryMapping::GetCountryTag(const std::string& titleID) const
{
  auto findIter = mapping.find(titleID);
  if (findIter == mapping.end())
    throw std::runtime_error("Failed to find a matching country for title " + titleID);
  return findIter->second;
}

} // LI_EU4