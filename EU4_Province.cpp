#include "EU4_Province.h"

namespace EU4 {

Province::Province(int id, const std::string& name, const Parser::ItemSet& historyItems)
: id(id), name(name), baseTax(0), manpower(0), extraCost(0)
{
  for (const auto& item : historyItems)
  {
    if (item->key == "culture")
      culture = item->value;
    else if (item->key == "religion")
      religion = item->value;
    else if (item->key == "base_tax")
      baseTax = std::stoi(item->value);
    else if (item->key == "manpower")
      manpower = std::stoi(item->value);
    else if (item->key == "capital")
      capital = item->value;
    else if (item->key == "discovered_by")
      discoveredByTechGroups.insert(item->value);
    else if (item->key == "extra_cost")
      extraCost = std::stoi(item->value);
    else if (!item->items.empty() && item->items[0]->key == "add_permanent_province_modifier")
    {
      const auto& modifiers = item->items[0]->items;
      for (const auto& modifier : modifiers)
        if (modifier->key == "name")
          permanentModifiers.insert(modifier->value);
    }
    HandleHistoryItem(*item);
  }
}

void Province::SetCulture(const std::string& newCulture)
{
  culture = newCulture;
}

void Province::WriteHistory(std::ostream& out, const CountryCollection& countries) const
{
  OnWriteHistory(out, countries);
  out << "culture = " << culture << '\n'
      << "religion = " << religion << '\n'
      << "hre = no\n" // the HRE is not converted
      << "base_tax = " << baseTax << '\n'
      << "manpower = " << manpower << '\n'
      << "capital = " << capital << '\n';
  for (const auto& techGroup : discoveredByTechGroups)
    out << "discovered_by = " << techGroup << '\n';
  if (extraCost != 0)
    out << "extra_cost = " << extraCost << '\n';
  for (const auto& permanentModifier : permanentModifiers)
  {
    out << '\n'
        << "100.1.1 = {\n"
        << "  add_permanent_province_modifier = {\n"
        << "    name = " << permanentModifier << '\n'
        << "    duration = -1\n"
        << "  }\n"
        << "}\n";
  }
}

} // EU4