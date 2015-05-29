#include "StringUtilities.h"

#include <locale>

std::string TrimWhitespace(const std::string& text)
{
  auto newBegin = text.find_first_not_of(" \t\n");
  if (newBegin == std::string::npos)
    return "";
  auto newEnd = text.find_last_not_of(" \t\n");
  return text.substr(newBegin, newEnd - newBegin + 1);
}

std::vector<std::string> SplitString(const std::string& text, char delimiter)
{
  std::vector<std::string> result;
  size_t beginPos = 0;
  size_t delimPos = 0;
  while (delimPos != std::string::npos)
  {
    delimPos = text.find(delimiter, delimPos + 1);
    if (delimPos == std::string::npos)
      result.emplace_back(text.substr(beginPos));
    else
      result.emplace_back(text.substr(beginPos, delimPos - beginPos));
    beginPos = delimPos + 1;
  }
  return result;
}

std::string LatinToUTF8(const std::string& text)
{
  std::string utf8text;
  for (unsigned char c : text)
    if (c < 128) 
      utf8text.push_back(c);
    else  // TBD: Proper conversion rules for CP-1252
      utf8text.push_back('?');
  return utf8text;
}