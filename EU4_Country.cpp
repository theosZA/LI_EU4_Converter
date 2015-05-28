#include "EU4_Country.h"

namespace EU4 {

Country::Country(std::string tag, std::string name, std::string adjective, Colour colour)
: tag(tag), name(name), adjective(adjective), colour(colour)
{}

void Country::WriteCommonInfo(std::ostream& out) const
{
  out << "# Country name: " << name << "\n\n"
      << "graphical_culture = westerngfx\n\n";

#ifdef MONOCOLOUR_TEST
  out << "color = { 20 20 255 }\n";
#else
  out << "color = { " << colour << " }\n";
#endif
}

void Country::WriteHistory(std::ostream& out) const
{
  out << "government = feudal_monarchy\n"
      << "technology_group = western\n"
      << "religion = catholic\n"
      << "primary_culture = english\n"
      << "capital = 1\n\n"
      << "1440.1.1 = {\n"
      << "  monarch = {\n"
      << "    name = \"Tester\"\n"
      << "    dynasty = \"McTestison\"\n"
      << "    birth_date = 1400.1.1\n"
      << "    adm = 6\n"
      << "    dip = 5\n"
      << "    mil = 4\n"
      << "  }\n"
      << "}\n";
}

void Country::WriteLocalisation(std::ostream& out) const
{
  out << ' ' << tag << ": \"" << name << "\"\n"
      << ' ' << tag << "_ADJ: \"" << adjective << "\"\n";
}

} // namespace EU4