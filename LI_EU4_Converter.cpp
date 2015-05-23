#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Converter.h"

int main(int argc, const char* argv[])
{
  try
  {
    if (argc < 3)
    {
      std::cout << "Missing command line arguments. Syntax:\n"
                << "LI_EU4_Converter.exe [EU4 path] [Output mod name]\n";
      return 2;
    }
    
    std::string eu4Path = argv[1];
    std::string eu4ModPath = eu4Path + "\\mod";
    std::string outputName = argv[2];

    std::cout << "Start\n";

    Converter converter;
    converter.CreateMod(outputName, eu4ModPath, eu4Path);

    std::cout << "Done\n";
  }
  catch (std::exception& e)
  {
    std::cerr << "Fatal error: " << e.what() << '\n';
    return 1;
  }
}