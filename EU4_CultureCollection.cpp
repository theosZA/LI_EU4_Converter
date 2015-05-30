#include "EU4_CultureCollection.h"

#include "CK2_CultureCollection.h"

namespace EU4 {

CultureCollection::CultureCollection(const CK2::CultureCollection& source, const CK2::Localisation& localisation)
{
  for (const auto& sourceCultureGroup : source.cultureGroups)
    cultureGroups.emplace(sourceCultureGroup.first, CultureGroup(sourceCultureGroup.second, localisation));
}

void CultureCollection::WriteToStream(std::ostream& out) const
{
  for (const auto& cultureGroup : cultureGroups)
    cultureGroup.second.WriteToStream(out);  
}

void CultureCollection::WriteLocalisations(std::ostream& out) const
{
  out << "l_english:\n";
  for (const auto& cultureGroup : cultureGroups)
    cultureGroup.second.WriteLocalisations(out);
}

} // EU4