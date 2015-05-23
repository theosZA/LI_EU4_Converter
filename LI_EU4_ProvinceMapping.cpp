#include "LI_EU4_ProvinceMapping.h"

#include "EU4_Parser.h"
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
  auto items = EU4::Parser::Parse(in);
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

} // LI_EU4