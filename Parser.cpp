#include "Parser.h"

#include <algorithm>
#include <sstream>
#include <stdexcept>

#include "StringUtilities.h"

namespace Parser {

std::unique_ptr<Item> ParseItem(const std::string& itemText)
{
  // Item is split as key = value.
  auto equalPos = itemText.find('=');

  auto key = TrimWhitespace(itemText.substr(0, equalPos));
  if (key.empty())
    return nullptr; // All items must have a key.

  std::unique_ptr<Item> item(new Item);
  item->key = std::move(key);

  std::string value = TrimWhitespace(itemText.substr(equalPos + 1));
  if (value.size() >= 2 && value.front() == '{' && value.back() == '}')
    // This is a complex value that needs to be further passed.
    item->items = Parse(std::istringstream(value.substr(1, value.size() - 2)));
  else
    item->value = value;

  return item;
}

ItemSet Parse(std::istream& in)
{
  ItemSet items;

  std::string currentItem;
  int openBraces = 0;
  while (!in.eof() && !in.fail())
  {
    std::string currentLine;
    std::getline(in, currentLine);

    auto commentPos = currentLine.find('#');
    if (commentPos != std::string::npos)
      currentLine.erase(commentPos); // remove any comment

    if (!currentItem.empty())
      currentItem.push_back('\n');  // preserve new-lines within an item
    currentItem += currentLine;
    openBraces += std::count(currentLine.begin(), currentLine.end(), '{');
    openBraces -= std::count(currentLine.begin(), currentLine.end(), '}');
    if (openBraces <= 0)
    {
      auto lastCharPos = currentItem.find_last_not_of(" \t");
      if (lastCharPos != std::string::npos && currentItem[lastCharPos] != '=')
      {
        auto parsedItem = ParseItem(currentItem);
        if (parsedItem)
          items.push_back(std::move(parsedItem));
        currentItem.clear();
        openBraces = 0;
      }
    }
  }

  return items;
}

const Item& GetItem(const ItemSet& items, const std::string& key)
{
  for (const auto& item : items)
    if (item->key == key)
      return *item;
  throw std::runtime_error("Failed to find item with key '" + key + "'");
}

} // Parser
