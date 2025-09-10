#include <fstream>
#include <sstream>
#include "file_utils.h"

std::string readFile(const std::string& filepath) {
    std::ifstream ifs(filepath);
    if (!ifs.is_open()) {
        throw std::runtime_error("Failed to open file: " + filepath);
    }
    std::stringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}
