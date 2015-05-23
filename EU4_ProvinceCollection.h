#include <functional>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "EU4_Province.h"

namespace EU4 {

// Holds a collection of all provinces in the EU4 map.
class ProvinceCollection
{
  public:
    // Constructor initializes the provinces from the files in the given path.
    // Only provinces in the given list of province IDs are included.
    ProvinceCollection(const std::set<int> provinceIDs, const std::string& provincePath);

    // Sets the owner and controller of all provinces to the specified country for debugging purposes.
    // It can be used to see if there are any gaps in the coverage of the map.
    void ResetOwnerForAllProvinces(const std::string& tag);

    // Writes province history to files added to the given path.
    void WriteHistoryToFiles(const std::string& path, const std::function<std::string(const std::string&)>& tagToName) const;

  private:
    std::vector<Province> provinces;
    std::map<int, std::string> provinceHistoryFileNames;
};

} // EU4