#pragma once

#include <istream>
#include <map>
#include <string>
#include <vector>

namespace CK2 {

// Holds all text localisations created for a CK2 mod.
class Localisation
{
  public:
    // Adds all localisations from the given source.
    void AddLocalisations(std::istream&);

    // Returns the localisation of the given text in the specified language.
    // If there is no translation (or is empty) for that language, returns the first
    // available translation for that text.
    // Only if there are no possible translations then an empty string is returned.
    const std::string& GetLocalisation(const std::string& key, size_t languageIndex) const;

  private:
    std::map<std::string, std::vector<std::string>> localisations;
};

} // CK2