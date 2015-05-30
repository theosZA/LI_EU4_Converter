#include "EU4_CultureGroup.h"

#include "CK2_CultureGroup.h"
#include "CK2_Localisation.h"

namespace EU4 {

CultureGroup::CultureGroup(const CK2::CultureGroup& source, const CK2::Localisation& localisation)
: id(source.id), name(localisation.GetLocalisation(source.id, 0))
{
  for (const auto& sourceCulture : source.cultures)
    cultures.emplace(sourceCulture.first, Culture(sourceCulture.second, localisation));
}

void CultureGroup::WriteToStream(std::ostream& out) const
{
  out << id << " = {\n";
  for (const auto& culture : cultures)
    culture.second.WriteToStream(out);
  out << "}\n";
}

void CultureGroup::WriteLocalisations(std::ostream& out) const
{
  out << ' ' << id << ": \"" << name << "\"\n";
  for (const auto& culture : cultures)
    culture.second.WriteLocalisation(out);
}

} // EU4