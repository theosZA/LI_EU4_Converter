#pragma once

#include <string>
#include <vector>

// Removes spaces before and after the text.
std::string TrimWhitespace(const std::string& text);

// Splits a string into a sequence of sub-strings separated by the given delimiter character.
std::vector<std::string> SplitString(const std::string& text, char delimiter);

// Converts ANSI text (ISO-Latin-1) to UTF-8.
std::string LatinToUTF8(const std::string& text);