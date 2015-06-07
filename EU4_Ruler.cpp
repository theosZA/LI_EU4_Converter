#include "EU4_Ruler.h"

#include "CK2_Character.h"

namespace EU4 {

int ConvertScore(int ck2Score)
{
  if (ck2Score <= 0)
    return 0;
  else if (ck2Score <= 2)
    return 1;
  else if (ck2Score <= 4)
    return 2;
  else if (ck2Score <= 6)
    return 3;
  else if (ck2Score <= 8)
    return 4;
  else if (ck2Score <= 10)
    return 5;
  else
    return 6;
}

Ruler::Ruler(const CK2::Character& character)
: name(character.birthName),
  dynasty("unknown"),
  female(character.female),
  birthDate(character.birthDate),
  ruleDate(1444, 11, 11),
  // Simple A/D/M  based on CK2 stewardship, diplomacy and military scores.
  admin(ConvertScore(character.GetStewardship())),
  diplo(ConvertScore(character.GetDiplomacy())),
  military(ConvertScore(character.GetMilitary()))
{}

void Ruler::WriteToStream(std::ostream& out) const
{
  out << ruleDate << " = {\n"
      << "  monarch = {\n"
      << "    name = \"" << name << "\"\n"
      << "    dynasty = \"" << dynasty << "\"\n"
      << "    birth_date = " << birthDate << '\n'
      << "    adm = " << admin << '\n'
      << "    dip = " << diplo << '\n'
      << "    mil = " << military << '\n';
  if (female)
    out << "    female = yes" << '\n';
  out << "  }\n"
      << "}\n";
}

} // EU4