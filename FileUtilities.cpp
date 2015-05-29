#include "FileUtilities.h"

#include <direct.h>
#include <windows.h>

namespace FileUtilities {

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

#pragma push_macro("CopyFile")
#undef CopyFile
void CopyFile(const std::string& sourceFile, const std::string& destFile)
{
#pragma pop_macro("CopyFile")
  ::CopyFileA(sourceFile.c_str(), destFile.c_str(), FALSE);
}

} // FileUtilities