#pragma once

#include <ostream>

#include "Date.h"

namespace CK2 {
class Character;
class Dynasty;
} // CK2

namespace EU4 {

// Represents a ruler of an EU4 country.
class Ruler
{
  public:
    Ruler(const CK2::Character&);

    void SetDynasty(const CK2::Dynasty&);

    void WriteToStream(std::ostream&) const;

  private:
    std::string name;
    std::string dynasty;
    bool female;

    Date birthDate;
    Date ruleDate;

    int admin;
    int diplo;
    int military;
};

} // EU4