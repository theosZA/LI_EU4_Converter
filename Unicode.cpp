#include "Unicode.h"

#include <cstdint>
#include <ostream>
#include <sstream>

namespace Unicode {

std::uint16_t Windows1252ToBmpCodePoint(unsigned char c)
{
  if (c <= 0x7F)
    // ASCII
    return static_cast<std::uint16_t>(c);

  if (c >= 0xA0)
    // Same as ISO-8859-1 and so maps naturally to the equivalent code point
    return static_cast<std::uint16_t>(c);

  // CP-1252 special characters mostly map to symbols in the BMP.
  switch (c)
  {
    case 0x80:  return 0x20AC;  // EURO SIGN
    case 0x82:  return 0x201A;  // SINGLE LOW-9 QUOTATION MARK
    case 0x83:  return 0x0192;  // LATIN SMALL LETTER F WITH HOOK
    case 0x84:  return 0x201E;  // DOUBLE LOW-9 QUOTATION MARK
    case 0x85:  return 0x2026;  // HORIZONTAL ELLIPSIS
    case 0x86:  return 0x2020;  // DAGGER
    case 0x87:  return 0x2021;  // DOUBLE DAGGER
    case 0x88:  return 0x02C6;  // MODIFIER LETTER CIRCUMFLEX ACCENT
    case 0x89:  return 0x2030;  // PER MILLE SIGN
    case 0x8A:  return 0x0160;  // LATIN CAPITAL LETTER S WITH CARON
    case 0x8B:  return 0x2039;  // SINGLE LEFT-POINTING ANGLE QUOTATION MARK
    case 0x8C:  return 0x0152;  // LATIN CAPITAL LIGATURE OE
    case 0x8E:  return 0x017D;  // LATIN CAPITAL LETTER Z WITH CARON
    case 0x91:  return 0x2018;  // LEFT SINGLE QUOTATION MARK
    case 0x92:  return 0x2019;  // RIGHT SINGLE QUOTATION MARK
    case 0x93:  return 0x201C;  // LEFT DOUBLE QUOTATION MARK
    case 0x94:  return 0x201D;  // RIGHT DOUBLE QUOTATION MARK
    case 0x95:  return 0x2022;  // BULLET
    case 0x96:  return 0x2013;  // EN DASH
    case 0x97:  return 0x2014;  // EM DASH
    case 0x98:  return 0x02DC;  // SMALL TILDE
    case 0x99:  return 0x2122;  // TRADE MARK SIGN
    case 0x9A:  return 0x0161;  // LATIN SMALL LETTER S WITH CARON
    case 0x9B:  return 0x203A;  // SINGLE RIGHT-POINTING ANGLE QUOTATION MARK
    case 0x9C:  return 0x0153;  // LATIN SMALL LIGATURE OE
    case 0x9E:  return 0x017E;  // LATIN SMALL LETTER Z WITH CARON
    case 0x9F:  return 0x0178;  // LATIN CAPITAL LETTER Y WITH DIAERESIS  
    default:    return 0xFFFD;  // Undefined - use replacement character
  }
}

// Creates a char of a form like 1110xxxx where the x bits are from a 16-bit value.
// Bit indexes are 0 from the lowest-order bit to 15 for the highest-order bit.
// Begin should be the first (lowest) bit and end should be one past the last (highest) bit.
// The char is always front-padded with a sequence of ones ending in a zero.
char BuildCharFromCodePointFragment(std::uint16_t bmpCodePoint, size_t bitIndexBegin, size_t bitIndexEnd)
{
  size_t bits = bitIndexEnd - bitIndexBegin;
  std::uint16_t mask = (1 << bits) - 1;
  unsigned char fragment = static_cast<unsigned char>((bmpCodePoint >> bitIndexBegin) & mask);
  for (size_t extraOneBitIndex = bits + 1; extraOneBitIndex < 8; ++extraOneBitIndex)
    fragment |= (1 << extraOneBitIndex);
  return static_cast<char>(fragment);
}


void EncodeBmpCodePointAsUTF8(std::uint16_t bmpCodePoint, std::ostream& out)
{
  if (bmpCodePoint <= 0x007f)
    // single byte UTF-8 character (7 bits)
    out << static_cast<char>(bmpCodePoint);
  else if (bmpCodePoint <= 0x07ff) 
    // two byte UTF-8 character (11 bits)
    out << BuildCharFromCodePointFragment(bmpCodePoint, 6, 11)  // 110xxxxx
        << BuildCharFromCodePointFragment(bmpCodePoint, 0, 6);  // 10xxxxxx
  else
    // three byte UTF-8 character (16 bits)
    out << BuildCharFromCodePointFragment(bmpCodePoint, 12, 16) // 1110xxxx
        << BuildCharFromCodePointFragment(bmpCodePoint, 6, 12)  // 10xxxxxx
        << BuildCharFromCodePointFragment(bmpCodePoint, 0, 6);  // 10xxxxxx
}

std::string Windows1252ToUTF8(const std::string& windows1252Text)
{
  std::ostringstream utf8Text;
  for (char c : windows1252Text)
    EncodeBmpCodePointAsUTF8(Windows1252ToBmpCodePoint(c), utf8Text);
  return utf8Text.str();
}

} // Unicode