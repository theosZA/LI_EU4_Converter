#include "EU4_EmptyProvince.h"

namespace EU4 {

void EmptyProvince::OnWriteHistory(std::ostream& out, const CountryCollection&) const
{
  out << "native_size = 60\n"
      << "native_ferocity = 4\n"
      << "native_hostileness = 8\n"
      << "trade_goods = unkmown\n";
}

} // EU4
