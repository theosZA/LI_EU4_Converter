#include "EU4_CountryCollection.h"

#include <fstream>
#include <stdexcept>

#include "CK2_TitleCollection.h"
#include "Log.h"

namespace EU4 {

// Strip out all characters that aren't just standard letters (A-Z,a-z).
std::string NormalizeName(const std::string& name)
{
  std::string normalized;
  for (char c : name)
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
      normalized.push_back(c);
  return normalized;
}

CountryCollection::CountryCollection(const CK2::TitleCollection& titles)
{
  LOG(LogLevel::Info) << "Creating EU4 countries";
  auto topLevelTitles = titles.GetAllTopLevelTitles();
  for (const auto& titleID : topLevelTitles)
  {
    const auto& title = titles.GetTitle(titleID);
    auto countryTag = titleCountryMapping.AddTitleAsNewCountry(titleID);
    EU4::Country country(countryTag, title);
    countries.emplace(countryTag, std::move(country));
    LOG(LogLevel::Debug) << "CK2 title " << titleID << " converted to country tag " << countryTag;
  }
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

const Country& CountryCollection::GetCountryByTitle(const std::string& titleID) const
{
  return GetCountry(titleCountryMapping.GetCountryTag(titleID));
}

Country& CountryCollection::GetCountryByTitle(const std::string& titleID)
{
  return GetCountry(titleCountryMapping.GetCountryTag(titleID));
}

const Country* CountryCollection::GetOptionalCountryByTitle(const std::string& titleID) const
{
  auto countryTag = titleCountryMapping.GetOptionalCountryTag(titleID);
  if (countryTag.empty())
    return nullptr;
  return &GetCountry(countryTag);
}

void CountryCollection::WriteTags(const std::string& fileName) const
{
  std::ofstream tagsFile(fileName);
  if (!tagsFile)
    throw std::runtime_error("Error creating tags file");
  for (const auto& countryPair : countries)
    tagsFile << countryPair.first << " = " << "countries/" << NormalizeName(countryPair.second.GetName()) << ".txt\n";
}

void CountryCollection::WriteCommonInfo(const std::string& path) const
{
  for (const auto& countryPair : countries)
  {
    const auto& country = countryPair.second;
    std::ofstream commonFile(path + '\\' + NormalizeName(country.GetName()) + ".txt");
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
    std::ofstream historyFile(path + '\\' + country.GetTag() + " - " + NormalizeName(country.GetName()) + ".txt");
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
  localisationCountriesFile << char(0xEF) << char(0xBB) << char(0xBF) // UTF-8 BOM required by EU4
                            << "l_english:\n";
  for (const auto& countryPair : countries)
    countryPair.second.WriteLocalisation(localisationCountriesFile);
}

} // EU4