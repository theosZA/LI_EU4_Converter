#include <string>
#include <vector>

// Returns all files in the specified folder.
std::vector<std::string> GetAllFilesInFolder(const std::string& path);

// Creates the folder if missing and returns the path as a string.
const std::string& MakeFolder(const std::string& newPath);