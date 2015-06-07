#pragma once

#include <string>

namespace Parser {
struct Item;
} // Parser

namespace CK2 {

// Represents a dynasty in CK2.
class Dynasty
{
  public:
    Dynasty(const Parser::Item& dynastyItem);

    int GetID() const { return id; }
    const std::string& GetName() const { return name; }

  private:
    int id;
    std::string name;
};

} // CK2