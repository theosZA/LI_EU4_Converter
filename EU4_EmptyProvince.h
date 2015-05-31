#pragma once

#include "EU4_Province.h"

namespace EU4 {

// An unsettled province in EU4.
class EmptyProvince : public Province
{
  public:
    EmptyProvince(int id, const std::string& name, const Parser::ItemSet& historyItems)
    : Province(id, name, historyItems)
    {}

  private:
    void OnWriteHistory(std::ostream&, const CountryCollection&) const override;
};

} // EU4