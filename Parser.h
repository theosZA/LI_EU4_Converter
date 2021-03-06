#pragma once

#include <istream>
#include <memory>
#include <string>
#include <vector>

namespace Parser {

struct Item;
typedef std::vector<std::unique_ptr<Item>> ItemSet;

// An EU4 item is a key-value pair where the value is
// either a straightforward value (stored as a string)
// or a collection of more items.
struct Item
{
  std::string key;
  // One of the following will be non-empty.
  ItemSet items;
  std::string value;
};

// Reads an EU4 file, splitting it up into items (normally from one item per line).
ItemSet Parse(std::istream&);

// Returns the item in a item set with the given key.
const Item& GetItem(const ItemSet&, const std::string& key);

} // Parser
