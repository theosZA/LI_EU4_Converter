#include "CK2_Character.h"

#include <sstream>

#include "Parser.h"
#include "StringUtilities.h"

namespace CK2 {

Character::Character(const Parser::Item& characterItem)
: id(std::stoi(characterItem.key)),
  female(false)
{
  for (const auto& subItem : characterItem.items)
  {
    if (subItem->key == "birth_name")
      birthName = StripQuotes(subItem->value);
    else if (subItem->key == "dynasty")
      dynasty = std::stoi(subItem->value);
    else if (subItem->key == "female")
      female = (subItem->value == "yes");
    else if (subItem->key == "birth_date")
      birthDate = Date(StripQuotes(subItem->value));
    else if (subItem->key == "attributes")
    {
      std::istringstream attributeStream(subItem->items[0]->key);
      for (auto& attribute : attributes)
        attributeStream >> attribute;
    }
    else if (subItem->key == "traits")
    {
      std::istringstream traitStream(subItem->items[0]->key);
      while (!traitStream.eof() && !traitStream.fail())
      {
        int newTrait;
        traitStream >> newTrait;
        traits.insert(newTrait);
      }
    }
    else if (subItem->key == "religion")
      religion = StripQuotes(subItem->value);
    else if (subItem->key == "culture")
      culture = StripQuotes(subItem->value);
  }
}

// TBD: For now these are just base values; they need to take into account traits, etc.

int Character::GetDiplomacy() const
{
  return attributes[0];
}

int Character::GetStewardship() const
{
  return attributes[1];
}

int Character::GetMilitary() const
{
  return attributes[2];
}

int Character::GetIntrigue() const
{
  return attributes[3];
}

int Character::GetLearning() const
{
  return attributes[4];
}

} // CK2