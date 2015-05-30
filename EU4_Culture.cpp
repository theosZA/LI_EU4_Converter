#include "EU4_Culture.h"

#include <algorithm>

#include "CK2_Culture.h"
#include "CK2_Localisation.h"

namespace EU4 {

Culture::Culture(const CK2::Culture& source, const CK2::Localisation& localisation)
: id(source.id), name(localisation.GetLocalisation(source.id, 0)), maleNames(source.maleNames), femaleNames(source.femaleNames)
{
  static const std::vector<std::string> eu4Graphics
    { "westerngfx", "easterngfx", "muslimgfx", "indiangfx", "asiangfx", "africangfx", "northamericagfx", "southamericagfx", "inuitgfx" };
  static const std::vector<std::vector<std::string>> ck2Graphics
    { { "frankishgfx", "englishgfx", "germangfx", "occitangfx", "southerngfx", "celticgfx", "norsegfx", "knightsgfx", "republicsgfx",
        "saxongfx", "normangfx", "northmangfx", "southgothgfx", "gaelicgfx", "latingfx", "holygfx", "norseholygfx", "balticholygfx",
        "finnishholygfx", "sarmatobritongfx", "westerngfx", "hedgeknightsgfx" }, // Western
      { "easternslavicgfx", "westernslavicgfx", "byzantinegfx", "indohellengfx", "alangfx", "cumangfx", "slavicholygfx", "orthodoxholygfx",
        "hellengfx", "easterngfx", "rhodokigfx", "elitespearwallgfx" }, // Eastern
      { "arabicgfx", "turkishgfx", "oldturkishgfx", "mongolgfx", "andalusiangfx", "levantinegfx", "ancientgfx", "berbergfx", "bektashigfx",
        "hashshashingfx", "immortalsgfx", "persiangfx", "oldpersiangfx", "egyptiangfx", "desertgfx", "zigguratgfx", "muslimgfx", "jewishgfx",
        "jewishholygfx" }, // Muslim
      { "hindugfx", "jaingfx", "buddhistgfx", "indiangfx" }, // Indian
      { "eastasiangfx", "centralasiangfx" }, // Asian
      { "africangfx", "east_africangfx", "westafricangfx", "westafricanholygfx" }, // African
      { "mesoamericangfx", "aztecholygfx" }, // North American
      { }, // South American
      { } // Intuit
    };

  auto ck2GraphicGroupIter = std::find_if(ck2Graphics.begin(), ck2Graphics.end(),
      [&](const std::vector<std::string>& ck2GraphicGroup)
      {
        auto ck2GraphicIter = std::find(ck2GraphicGroup.begin(), ck2GraphicGroup.end(), source.unitGraphicalCulture);
        return (ck2GraphicIter != ck2GraphicGroup.end());
      });
  if (ck2GraphicGroupIter != ck2Graphics.end())
    graphicalCulture = eu4Graphics[std::distance(ck2Graphics.begin(), ck2GraphicGroupIter)];
}

void Culture::WriteToStream(std::ostream& out) const
{
  out << '\t' << id << " = {\n"
      << "\t\tgraphical_culture = " << graphicalCulture << '\n'
      << "\t\tmale_names = {\n"
      << "\t\t\t";
  for (const auto& name : maleNames)
    out << name << ' ';
  out << "\n\t\t}\n"
      << "\t\tfemale_names = {\n"
      << "\t\t\t";
  for (const auto& name : femaleNames)
    out << name << ' ';
  out << "\n\t\t}\n"
      << "\t}\n";
}

void Culture::WriteLocalisation(std::ostream& out) const
{
  out << ' ' << id << ": \"" << name << "\"\n";
}

} // EU4