#include "FileUtilities.h"

#include <direct.h>
#include <windows.h>

std::vector<std::string> GetAllFilesInFolder(const std::string& path)
{
  std::vector<std::string> fileNames;
  WIN32_FIND_DATAA findFileData;
  HANDLE findHandle = FindFirstFileA((path + "\\*.*").c_str(), &findFileData);
  if (findHandle != INVALID_HANDLE_VALUE)
  {
    BOOL moreFiles = TRUE;
    while (moreFiles == TRUE)
    {
      std::string fileName = findFileData.cFileName;
      if (fileName != "." && fileName != "..")
        fileNames.push_back(findFileData.cFileName);
      moreFiles = FindNextFileA(findHandle, &findFileData);
    }
  }
  FindClose(findHandle);
  return fileNames;
}

const std::string& MakeFolder(const std::string& newPath)
{
  _mkdir(newPath.c_str());
  return newPath;
}