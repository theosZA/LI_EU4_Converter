#include "EU4_SettledProvince.h"

#include "EU4_CountryCollection.h"

namespace EU4 {

void SettledProvince::SetOwner(const std::string& tag)
{
  ownerTag = tag; 
}

void SettledProvince::SetController(const std::string& tag)
{
  controllerTag = tag;
}

void SettledProvince::ClearCores()
{
  coreTags.clear();
}

void SettledProvince::AddCore(const std::string& tag)
{
  coreTags.insert(tag);
}

void SettledProvince::HandleHistoryItem(const Parser::Item& historyItem)
{
  if (historyItem.key == "owner")
    ownerTag = historyItem.value;
  else if (historyItem.key == "controller")
    controllerTag = historyItem.value;
  else if (historyItem.key == "add_core")
    coreTags.insert(historyItem.value);
  else if (historyItem.key == "trade_goods")
    tradeGood = historyItem.value;
}

void SettledProvince::OnWriteHistory(std::ostream& out, const CountryCollection& countries) const
{
  out << "owner = " << ownerTag << " # " << countries.GetCountry(ownerTag).GetName() << '\n'
      << "controller = " << controllerTag << " # " << countries.GetCountry(controllerTag).GetName() << '\n';
  for (const auto& coreTag : coreTags)
    out << "add_core = " << coreTag << " # " << countries.GetCountry(coreTag).GetName() << '\n';
  if (!tradeGood.empty())
    out << "trade_goods = " << tradeGood << '\n';
}

} // EU4