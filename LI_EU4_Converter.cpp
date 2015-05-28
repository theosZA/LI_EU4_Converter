#include <iostream>
#include <stdexcept>
#include <string>

#include "CK2_World.h"
#include "EU4_World.h"
#include "Log.h"

int main(int argc, const char* argv[])
{
  try
  {
    if (argc < 5)
    {
      std::cout << "Missing command line arguments. Syntax:\n"
                << "LI_EU4_Converter.exe [LI mod path] [LI save] [EU4 path] [Output mod name]\n";
      return 2;
    }
    
    std::string liModPath = argv[1];
    std::string liFileName = argv[2];
    std::string eu4Path = argv[3];
    std::string eu4ModPath = eu4Path + "\\mod";
    std::string outputName = argv[4];

    LOG(LogLevel::Info) << "LI->EU4 converter v0.1a";

    LOG(LogLevel::Info) << "* Building CK2 world";
    CK2::World ck2World(liFileName, liModPath);
    LOG(LogLevel::Info) << "* Building EU4 world";
    EU4::World eu4World(ck2World, eu4Path);
    LOG(LogLevel::Info) << "* Writing EU4 mod " << outputName;
    eu4World.CreateMod(outputName, eu4ModPath);

    LOG(LogLevel::Info) << "Done";
  }
  catch (std::exception& e)
  {
    LOG(LogLevel::Error) << e.what();
    return 1;
  }
}