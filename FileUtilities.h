#pragma once

#include <string>
#include <vector>

namespace FileUtilities {

// Returns all files in the specified folder.
std::vector<std::string> GetAllFilesInFolder(const std::string& path);

// Creates the folder if missing and returns the path as a string.
const std::string& MakeFolder(const std::string& newPath);

// Copies source to dest, replacing dest if it already exists.
void CopyFile(const std::string& sourceFile, const std::string& destFile);

} // FileUtilities