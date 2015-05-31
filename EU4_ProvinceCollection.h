#pragma once

#include <map>
#include <memory>
#include <set>
#include <string>

#include "EU4_Province.h"

namespace CK2 {
class ProvinceCollection;
class TitleCollection;
}

namespace EU4 {

class CountryCollection;

// Holds a collection of all provinces in the EU4 map.
class ProvinceCollection
{
  public:
    // Constructor creates all the EU4 provinces from the countries and CK2 provinces and titles
    // using the mapping in the specified file. The province baseline comes from the files in the
    // given province path.
    ProvinceCollection(const CK2::ProvinceCollection&, const CK2::TitleCollection&, const CountryCollection&,
                       const std::string& provinceMappingFileName, const std::string& provincePath);

    const Province& GetProvince(int provinceID) const;
    Province& GetProvince(int provinceID);

    // Writes province history to files added to the given path.
    void WriteHistoryToFiles(const std::string& path, const CountryCollection&) const;

  private:
    // Reads province history for the given provinces from files in the given path.
    void ReadProvincesFromFiles(const std::set<int>& provinceIDs, const std::string& path, bool settled);

    std::map<int, std::unique_ptr<Province>> provinces;
    std::map<int, std::string> provinceHistoryFileNames;
};

} // EU4