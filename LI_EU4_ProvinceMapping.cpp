#include "LI_EU4_ProvinceMapping.h"

#include <stdexcept>
#include <string>

#include "Parser.h"

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
    mapping.emplace(std::stoi(item->value), SplitIntList(item->key));
}

std::set<int> ProvinceMapping::GetAllEU4ProvinceIDs() const
{
  std::set<int> eu4ProvinceIDs;
  for (const auto& mappingPair : mapping)
    eu4ProvinceIDs.insert(mappingPair.first);
  return eu4ProvinceIDs;
}

const std::vector<int>& ProvinceMapping::GetCK2ProvinceIDs(int eu4ProvinceID) const
{
  auto findIter = mapping.find(eu4ProvinceID);
  if (findIter == mapping.end())
    throw std::runtime_error("Failed to find CK2 provinces corresponding to EU4 province " + std::to_string(eu4ProvinceID));
  return findIter->second;  
}

} // LI_EU4