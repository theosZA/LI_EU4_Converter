#pragma once

#include <map>
#include <string>

#include "EU4_CultureGroup.h"

namespace CK2 {
class CultureCollection;
class Localisation;
}

namespace EU4 {

// Holds all culture groups and their specific cultures.
class CultureCollection
{
  public:
    CultureCollection(const CK2::CultureCollection&, const CK2::Localisation&);

    void WriteToStream(std::ostream&) const;
    void WriteLocalisations(std::ostream&) const;

  private:
    std::map<std::string, CultureGroup> cultureGroups;
};

} // EU4