#include <ostream>
#include <string>

namespace EU4 {

// A country (corresponds to a tag) in EU4.
class Country
{
  public:
    // Default constructor for testing creates a made-up country of Testonia.
    Country();

    // Returns this country's tag.
    const std::string& GetTag() const { return tag; }
    // Returns the contry's name.
    const std::string& GetName() const { return name; }

    // Writes the country's common information such as colour.
    void WriteCommonInfo(std::ostream&) const;
    // Writes the country's history including current situation such as current government, religion and rulers.
    void WriteHistory(std::ostream&) const;
    // Writes the country's name and adjective for localisation.
    void WriteLocalisation(std::ostream&) const;

  private:
    std::string tag;
    std::string name;
    std::string adjective;

    // Common (some of these may be optional)
    // TBD: graphical culture
    // TBD: colour
    // TBD: historical idea groups? try use dynamic idea groups
    // TBD: historical units
    // TBD: monarch names
    // TBD: leader names
    // TBD: ship names
    // TBD: army names
    // TBD: fleet names

    // History
    // TBD: government
    // TBD: mercantilism
    // TBD: technology group
    // TBD: religion
    // TBD: primary culture
    // TBD: capital province
    // TBD: rulers/heirs
};

} // namespace EU4