#pragma once

#include <ostream>
#include <string>

struct Date
{
  int year;
  int month;
  int day;

  Date() : year(0), month(0), day(0) {}
  Date(int year, int month, int day) : year(year), month(month), day(day) {}

  // Constructor for a date in "YYYY.MM.DD" format.
  Date(const std::string&);

  bool operator()() { return year == 0 && month == 0 && day == 0; }

  friend std::ostream& operator<<(std::ostream&, const Date&);
};