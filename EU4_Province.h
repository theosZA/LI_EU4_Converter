#pragma once

#include <ostream>
#include <set>
#include <string>

#include "Parser.h"

namespace EU4 {

class CountryCollection;

// Base class for any EU4 province, settled or not.
class Province
{
  public:
    // Constructor based on an existing EU4 province history.
    Province(int id, const std::string& name, const Parser::ItemSet& historyItems);

    int GetID() const { return id; }
    const std::string& GetName() const { return name; }

    void SetCulture(const std::string& culture);

    // Writes the province's history including for example the current religion.
    void WriteHistory(std::ostream&, const CountryCollection&) const;

  protected:
    // Child classes to handle the given item from an EU4 province history.
    virtual void HandleHistoryItem(const Parser::Item& historyItem) {}
    // Child classes to add their own content such as owner info or native info.
    virtual void OnWriteHistory(std::ostream&, const CountryCollection&) const {}

  private:
    int id;
    std::string name;

    std::string culture;
    std::string religion;
    int baseTax;
    int manpower;
    std::string capital;
    int extraCost;

    std::set<std::string> discoveredByTechGroups;
    std::set<std::string> permanentModifiers;
};

} // EU4