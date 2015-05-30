#pragma once

#include <vector>

namespace MapUtilities {

// Returns all keys in the given map.
template <class MapType>
std::vector<typename MapType::key_type> GetKeys(const MapType& map)
{
  std::vector<MapType::key_type> result;
  for (const auto& i : map)
    result.emplace_back(i.first);
  return result;
}

// Returns all keys in the given map whose value is the maximum in the map (minimum of 0).
template <class MapType>
std::vector<typename MapType::key_type> GetKeysWithMaxValue(const MapType& map)
{
  MapType::mapped_type maxValue = 0;
  for (const auto& i : map)
    if (i.second > maxValue)
      maxValue = i.second;

  std::vector<MapType::key_type> result;
  for (const auto& i : map)
    if (i.second == maxValue)
      result.emplace_back(i.first);

  return result;
}


} // MapUtilities