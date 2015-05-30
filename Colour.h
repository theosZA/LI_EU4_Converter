#pragma once

#include <ostream>
#include <string>

struct Colour
{
  int red;
  int green;
  int blue;

  Colour() : red(0), green(0), blue(0) {}

  // Creates a colour from an RGB triplet such as "127 63 31"  
  Colour(const std::string& triplet);
  // Creates a colour from an RGB triplet such as "0.3 0.5 0.12"
  static Colour CreateFromFractions(const std::string& fracitonTriplet);

  friend std::ostream& operator<<(std::ostream&, const Colour&);
};