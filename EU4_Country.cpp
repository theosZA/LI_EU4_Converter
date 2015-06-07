#include "EU4_Country.h"

#include "CK2_CharacterCollection.h"
#include "CK2_Title.h"

namespace EU4 {

Country::Country(const std::string& tag, const CK2::Title& title, const CK2::CharacterCollection& characters)
: tag(tag), 
#ifdef MONOCOLOUR_TEST
  name(tag),
#else
  name(title.name), 
#endif
  adjective(title.adjective), 
  colour(title.colour),
  religion(characters.GetCharacter(title.holderID).GetReligion()),
  primaryCulture(characters.GetCharacter(title.holderID).GetCulture()),
  ruler(characters.GetCharacter(title.holderID))
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
      << "religion = " << religion << '\n'
      << "primary_culture = " << primaryCulture << '\n'
      << "capital = 1\n\n";
  ruler.WriteToStream(out);
}

void Country::WriteLocalisation(std::ostream& out) const
{
  out << ' ' << tag << ": \"" << name << "\"\n"
      << ' ' << tag << "_ADJ: \"" << adjective << "\"\n";
}

} // namespace EU4