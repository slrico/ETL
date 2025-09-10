#include <iostream>
#include <filesystem>
#include "file_utils.h"
#include "json_parser.h"
#include "etl_processor.h"
#include "rapidjson/document.h"

int main() {
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    const std::string filepath = "../data/large-file.json";

    std::string jsonStr;
    try {
        jsonStr = readFile(filepath);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    rapidjson::Document doc;
    doc.Parse(jsonStr.c_str());

    if (doc.HasParseError()) {
        std::cerr << "Parse error: " << doc.GetParseError()
                  << " (offset " << doc.GetErrorOffset() << ")" << std::endl;
        return 1;
    }

    inspectJsonStructure(doc);
    processEvents(doc);

    return 0;
}
