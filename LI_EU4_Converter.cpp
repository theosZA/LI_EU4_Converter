#include <iostream>
#include <stdexcept>

#include "Converter.h"

int main(int argc, const char* argv[])
{
  try
  {
    std::cout << "Start\n";

    Converter converter;
    converter.CreateMod("TestMod9000", "G:\\SteamLibrary\\SteamApps\\common\\Europa Universalis IV\\mod");

    std::cout << "Done\n";
  }
  catch (std::exception& e)
  {
    std::cerr << "Fatal error: " << e.what() << '\n';
  }
}