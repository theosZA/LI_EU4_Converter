#include "Date.h"

#include <stdexcept>

#include "StringUtilities.h"

Date::Date(const std::string& text)
{
  auto items = SplitString(text, '.');
  if (items.size() != 3)
    throw std::runtime_error("\"" + text + "\" is not in a valid date format YYYY.MM.DD");
  year = std::stoi(items[0]);
  month = std::stoi(items[1]);
  day = std::stoi(items[2]);
}

std::ostream& operator<<(std::ostream& out, const Date& date)
{
  out << date.year << '.' << date.month << '.' << date.day;
  return out;
}
