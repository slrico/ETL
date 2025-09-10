#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>

// Reads entire file contents and returns as a string.
// Throws an exception or errors if file can't be opened or read.
std::string readFile(const std::string& filepath);

#endif // FILE_UTILS_H
