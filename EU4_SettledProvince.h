#pragma once

#include "EU4_Province.h"

namespace EU4 {

// A settled province in EU4.
class SettledProvince : public Province
{
  public:
    SettledProvince(int id, const std::string& name, const Parser::ItemSet& historyItems)
    : Province(id, name, historyItems)
    {}

    void SetOwner(const std::string& tag);
    void SetController(const std::string& tag);
    void ClearCores();
    void AddCore(const std::string& tag);

  private:
    void HandleHistoryItem(const Parser::Item& historyItem) override;
    void OnWriteHistory(std::ostream&, const CountryCollection&) const override;

    std::string ownerTag;
    std::string controllerTag;
    std::set<std::string> coreTags;

    std::string tradeGood;
};

} // EU4