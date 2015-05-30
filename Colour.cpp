#include "Colour.h"

#include <sstream>

Colour::Colour(const std::string& triplet)
{
  std::istringstream input(triplet);
  input >> red >> green >> blue;
}

Colour Colour::CreateFromFractions(const std::string& fracitonTriplet)
{
  double red, green, blue;
  std::istringstream input(fracitonTriplet);
  input >> red >>  green >> blue;
  Colour colour;
  colour.red = static_cast<int>(red * 255);
  colour.green = static_cast<int>(green * 255);
  colour.blue = static_cast<int>(blue * 255);
  return colour;
}

std::ostream& operator<<(std::ostream& out, const Colour& colour)
{
  out << colour.red << ' ' << colour.green << ' ' << colour.blue;
  return out;
}
