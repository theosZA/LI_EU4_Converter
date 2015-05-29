#include "LI_EU4_TitleCountryMapping.h"

#include <stdexcept>

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

// Create tags GA0 through ZZ9 (5200 tags)
TitleCountryMapping::TitleCountryMapping()
: lastTag("FZ9")
{}

std::string TitleCountryMapping::AddTitleAsNewCountry(const std::string& titleID)
{
  IncrementTag(lastTag);
  mapping[titleID] = lastTag;
  return lastTag;
}

const std::string& TitleCountryMapping::GetCountryTag(const std::string& titleID) const
{
  auto findIter = mapping.find(titleID);
  if (findIter == mapping.end())
    throw std::runtime_error("Failed to find a matching country for title " + titleID);
  return findIter->second;
}

const std::string& TitleCountryMapping::GetOptionalCountryTag(const std::string& titleID) const
{
  auto findIter = mapping.find(titleID);
  if (findIter == mapping.end())
  {
    static const std::string noSuchTitle = "";
    return noSuchTitle;
  }
  return findIter->second;
}

} // LI_EU4