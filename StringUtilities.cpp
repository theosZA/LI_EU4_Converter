#include "StringUtilities.h"

std::string TrimWhitespace(const std::string& text)
{
  auto newBegin = text.find_first_not_of(" \t\n");
  auto newEnd = text.find_last_not_of(" \t\n");
  return text.substr(newBegin, newEnd - newBegin + 1);
}
