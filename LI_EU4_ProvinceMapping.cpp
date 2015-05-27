#include "LI_EU4_ProvinceMapping.h"

#include <string>

#include "CK2_ProvinceCollection.h"
#include "EU4_ProvinceCollection.h"
#include "LI_EU4_TitleCountryMapping.h"
#include "Log.h"
#include "Parser.h"
#include "StringUtilities.h"

namespace LI_EU4 {

std::vector<int> SplitIntList(std::string text)
{
  std::vector<int> numbers;
  while (!text.empty())
  {
    numbers.push_back(std::stoi(text));
    auto commaPos = text.find(',');
    if (commaPos == std::string::npos)
      text.clear();
    else
      text = text.substr(commaPos + 1);
  }
  return numbers;
}

ProvinceMapping::ProvinceMapping(std::istream& in)
{
  auto items = Parser::Parse(in);
  for (const auto& item : items)
    mapping[std::stoi(item->value)] = SplitIntList(item->key);
}

std::set<int> ProvinceMapping::GetAllEU4ProvinceIDs() const
{
  std::set<int> eu4ProvinceIDs;
  for (const auto& mappingPair : mapping)
    eu4ProvinceIDs.insert(mappingPair.first);
  return eu4ProvinceIDs;
}

void ProvinceMapping::ConvertProvinces(const CK2::ProvinceCollection& sourceProvinces, const CK2::TitleCollection& titles,
                                       const TitleCountryMapping& countryMapping, EU4::ProvinceCollection& destProvinces) const
{
  for (const auto& mappingPair : mapping)
  {
    auto destProvinceID = mappingPair.first;
    auto sourceProvinceID = mappingPair.second[0];  // For now we will just use whichever province is listed first. TBD: Use a real decision algorithm.
    auto sourceTitle = sourceProvinces.GetProvinceTopLevelTitle(sourceProvinceID, titles);
    std::string destCountryTag = countryMapping.GetCountryTag(sourceTitle);
    auto& destProvince = destProvinces.GetProvince(destProvinceID);
    destProvince.ResetOwner(destCountryTag);
    LOG(LogLevel::Debug) << "EU4 province " << destProvinceID << " from CK2 province " << sourceProvinceID << " (" << sourceTitle << " to tag " << destCountryTag << ')';
  }  
}

} // LI_EU4