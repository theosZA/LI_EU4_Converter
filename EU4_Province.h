#pragma once

#include <functional>
#include <istream>
#include <ostream>
#include <set>
#include <string>

namespace EU4 {

class CountryCollection;

// A settled province in EU4.
class Province
{
  public:
    // Constructor based on an existing EU4 province history.
    Province(int id, const std::string& name, std::istream&);

    void SetOwner(const std::string& tag);
    void SetController(const std::string& tag);
    void ClearCores();
    void AddCore(const std::string& tag);

    int GetID() const { return id; }
    const std::string& GetName() const { return name; }

    // Writes the province's history including current situation such as current owner and religion.
    void WriteHistory(std::ostream&, const CountryCollection&) const;

  private:
    int id;
    std::string name;

    std::string ownerTag;
    std::string controllerTag;
    std::set<std::string> coreTags;

    std::string culture;
    std::string religion;
    int baseTax;
    std::string tradeGood;
    int manpower;
    std::string capital;
    int extraCost;

    std::set<std::string> discoveredByTechGroups;
    std::set<std::string> permanentModifiers;
};

} // EU4