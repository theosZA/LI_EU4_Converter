#include "EU4_Country.h"

#include "CK2_CharacterCollection.h"
#include "CK2_DynastyCollection.h"
#include "CK2_Title.h"

namespace EU4 {

Country::Country(const std::string& tag, const CK2::Title& title, const CK2::CharacterCollection& characters, const CK2::DynastyCollection& dynasties)
: tag(tag), 
#ifdef MONOCOLOUR_TEST
  name(tag),
#else
  name(title.name), 
#endif
  adjective(title.adjective), 
  colour(title.colour)
{
  if (title.holderID != 0)
  {
    const auto& rulerCharacter = characters.GetCharacter(title.holderID);
    ruler.reset(new Ruler(characters.GetCharacter(title.holderID)));
    religion = rulerCharacter.religion;
    primaryCulture = rulerCharacter.culture;
    if (rulerCharacter.dynasty != 0)
      ruler->SetDynasty(dynasties.GetDynasty(rulerCharacter.dynasty));
  }
}

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
      << "technology_group = western\n";
  if (!religion.empty())
    out << "religion = " << religion << '\n';
  if (!primaryCulture.empty())
    out << "primary_culture = " << primaryCulture << '\n';
  if (ruler)
    ruler->WriteToStream(out);
}

void Country::WriteLocalisation(std::ostream& out) const
{
  out << ' ' << tag << ": \"" << name << "\"\n"
      << ' ' << tag << "_ADJ: \"" << adjective << "\"\n";
}

} // namespace EU4