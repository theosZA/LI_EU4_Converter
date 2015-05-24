#include "EU4_CountryCollection.h"

#include <fstream>
#include <stdexcept>

namespace EU4 {

void CountryCollection::AddCountry(Country&& country)
{
  countries.emplace(country.GetTag(), std::move(country));
}

const Country& CountryCollection::GetCountry(const std::string& countryTag) const
{
  return const_cast<const Country&>(const_cast<CountryCollection*>(this)->GetCountry(countryTag));
}

Country& CountryCollection::GetCountry(const std::string& countryTag)
{
  auto findIter = countries.find(countryTag);
  if (findIter == countries.end())
    throw std::runtime_error("Failed to find country with tag " + countryTag);
  return findIter->second;
}

void CountryCollection::WriteTags(const std::string& fileName) const
{
  std::ofstream tagsFile(fileName);
  if (!tagsFile)
    throw std::runtime_error("Error creating tags file");
  for (const auto& countryPair : countries)
    tagsFile << countryPair.first << " = " << "countries/" << countryPair.second.GetName() << ".txt\n";
}

void CountryCollection::WriteCommonInfo(const std::string& path) const
{
  for (const auto& countryPair : countries)
  {
    const auto& country = countryPair.second;
    std::ofstream commonFile(path + '\\' + country.GetName() + ".txt");
    if (!commonFile)
      throw std::runtime_error("Error creating common country file for country " + country.GetName());
    country.WriteCommonInfo(commonFile);
  }
}

void CountryCollection::WriteHistory(const std::string& path) const
{
  for (const auto& countryPair : countries)
  {
    const auto& country = countryPair.second;
    std::ofstream historyFile(path + '\\' + country.GetTag() + " - " + country.GetName() + ".txt");
    if (!historyFile)
      throw std::runtime_error("Error creating common history file for country " + country.GetName());
    country.WriteHistory(historyFile);
  }
}

void CountryCollection::WriteLocalisation(const std::string& fileName) const
{
  std::ofstream localisationCountriesFile(fileName);
  if (!localisationCountriesFile)
    throw std::runtime_error("Error creating countries localistion file");
  localisationCountriesFile << "l_english:\n";
  for (const auto& countryPair : countries)
    countryPair.second.WriteLocalisation(localisationCountriesFile);
}

} // EU4