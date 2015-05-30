#pragma once

#include <map>
#include <ostream>

#include "EU4_Culture.h"

namespace CK2 {
class CultureGroup;
class Localisation;
} // CK2

namespace EU4 {

// A culture group is a linked set of cultures.
class CultureGroup
{
  public:
    CultureGroup(const CK2::CultureGroup&, const CK2::Localisation&);

    void WriteToStream(std::ostream&) const;
    void WriteLocalisations(std::ostream&) const;

  private:
    std::string id;
    std::string name;
    std::map<std::string, Culture> cultures;
};

} // EU4