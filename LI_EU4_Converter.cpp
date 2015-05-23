#include <iostream>
#include <stdexcept>

int main(int argc, const char* argv[])
{
  try
  {
    std::cout << "Start\n";
    std::cout << "Done\n";
  }
  catch (std::exception& e)
  {
    std::cerr << "Fatal error: " << e.what() << '\n';
  }
}