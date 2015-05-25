#include "Colour.h"

#include <sstream>

Colour::Colour(const std::string& triplet)
{
  std::istringstream input(triplet);
  input >> red >> green >> blue;
}

std::ostream& operator<<(std::ostream& out, const Colour& colour)
{
  out << colour.red << ' ' << colour.green << ' ' << colour.blue;
  return out;
}
