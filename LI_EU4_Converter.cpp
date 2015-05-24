#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Converter.h"

int main(int argc, const char* argv[])
{
  try
  {
    if (argc < 4)
    {
      std::cout << "Missing command line arguments. Syntax:\n"
                << "LI_EU4_Converter.exe [LI save] [EU4 path] [Output mod name]\n";
      return 2;
    }
    
    std::string liFileName = argv[1];
    std::string eu4Path = argv[2];
    std::string eu4ModPath = eu4Path + "\\mod";
    std::string outputName = argv[3];

    std::cout << "Start\n";

    Converter converter;
    converter.ReadSave(liFileName);
    converter.CreateMod(outputName, eu4ModPath, eu4Path);

    std::cout << "Done\n";
  }
  catch (std::exception& e)
  {
    std::cerr << "Fatal error: " << e.what() << '\n';
    return 1;
  }
}