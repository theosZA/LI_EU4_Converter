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
    if (argc < 6)
    {
      std::cout << "Missing command line arguments. Syntax:\n"
                << "LI_EU4_Converter.exe [CK2 path] [LI mod path] [LI save] [EU4 path] [Output mod name]\n";
      return 2;
    }
    
    std::string ck2Path = argv[1];
    std::string liModPath = argv[2];
    std::string liFileName = argv[3];
    std::string eu4Path = argv[4];
    std::string eu4ModPath = eu4Path + "\\mod";
    std::string outputName = argv[5];

    LOG(LogLevel::Info) << "LI->EU4 converter v0.1a";

    LOG(LogLevel::Info) << "* Building CK2 world";
    CK2::World ck2World(ck2Path, liFileName, liModPath);
    LOG(LogLevel::Info) << "* Building EU4 world";
    EU4::World eu4World(ck2World, eu4Path);
    LOG(LogLevel::Info) << "* Writing EU4 mod " << outputName;
    eu4World.CreateMod(outputName, eu4ModPath, liModPath);

    LOG(LogLevel::Info) << "Done";
  }
  catch (std::exception& e)
  {
    LOG(LogLevel::Error) << e.what();
    return 1;
  }
}