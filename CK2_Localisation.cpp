#include "CK2_Localisation.h"

#include "StringUtilities.h"
#include "Unicode.h"

namespace CK2 {

void Localisation::AddLocalisations(std::istream& in)
{
  while (!in.eof() && !in.fail())
  {
    std::string currentLine;
    std::getline(in, currentLine);
    if (!currentLine.empty() && currentLine.front() != '#')
    {
      auto currentLocalisations = SplitString(currentLine, ';');
      if (!currentLocalisations.empty())
      {
        auto& newLocalisation = localisations[currentLocalisations[0]];
        newLocalisation.clear();  // replace old localisations with these newer ones
        for (size_t i = 1; i < currentLocalisations.size() - 1; ++i)
           newLocalisation.push_back(Unicode::Windows1252ToUTF8(currentLocalisations[i]));
      }
    }
  }
}

const std::string& Localisation::GetLocalisation(const std::string& key, size_t languageIndex) const
{
  static const std::string noLocalisation;

  auto findIter = localisations.find(key);
  if (findIter == localisations.end())
    return noLocalisation;

  const auto& currentLocalisations = findIter->second;
  if (languageIndex < currentLocalisations.size() && !currentLocalisations[languageIndex].empty())
    return currentLocalisations[languageIndex];

  // Need to find the first valid localisation for this key.
  for (const auto& localisation : currentLocalisations)
    if (!localisation.empty())
      return localisation;

  return noLocalisation;
}

} // CK2