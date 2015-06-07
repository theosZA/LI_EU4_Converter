#include "CK2_Dynasty.h"

#include "Parser.h"
#include "StringUtilities.h"

namespace CK2 {

Dynasty::Dynasty(const Parser::Item& dynastyItem)
: id(std::stoi(dynastyItem.key))
{
  for (const auto& subItem : dynastyItem.items)
  {
    if (subItem->key == "name")
      name = StripQuotes(subItem->value);
  }
}

} // CK2