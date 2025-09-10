#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include "rapidjson/document.h"

// Reads entire file contents into string
std::string readFile(const std::string& filepath) {
    std::ifstream ifs(filepath);
    if (!ifs.is_open()) {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return "";
    }
    std::stringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}

// Recursive function to print JSON value structure and sample content
void inspectJsonValue(const rapidjson::Value& val, int indent = 0) {
    std::string indentStr(indent, ' ');
    
    if (val.IsObject()) {
        std::cout << indentStr << "Object with " << val.MemberCount() << " members:" << std::endl;
        int count = 0;
        for (auto itr = val.MemberBegin(); itr != val.MemberEnd() && count < 5; ++itr, ++count) {
            std::cout << indentStr << "  Key: " << itr->name.GetString() << ", Type: ";
            if (itr->value.IsString()) std::cout << "String, Value: " << itr->value.GetString() << std::endl;
            else if (itr->value.IsInt()) std::cout << "Int, Value: " << itr->value.GetInt() << std::endl;
            else if (itr->value.IsDouble()) std::cout << "Double, Value: " << itr->value.GetDouble() << std::endl;
            else if (itr->value.IsArray()) std::cout << "Array" << std::endl;
            else if (itr->value.IsObject()) std::cout << "Object" << std::endl;
            else std::cout << "Other" << std::endl;
            
            // Recursive inspect for nested objects or arrays, increase indent
            if (itr->value.IsObject() || itr->value.IsArray())
                inspectJsonValue(itr->value, indent + 4);
        }
        if (val.MemberCount() > 5)
            std::cout << indentStr << "  ... and more members" << std::endl;
    }
    else if (val.IsArray()) {
        std::cout << indentStr << "Array with " << val.Size() << " elements" << std::endl;
        // Inspect up to 5 elements
        for (rapidjson::SizeType i = 0; i < val.Size() && i < 5; ++i) {
            std::cout << indentStr << "  Element " << i << ": ";
            if (val[i].IsString()) std::cout << "String, Value: " << val[i].GetString() << std::endl;
            else if (val[i].IsInt()) std::cout << "Int, Value: " << val[i].GetInt() << std::endl;
            else if (val[i].IsDouble()) std::cout << "Double, Value: " << val[i].GetDouble() << std::endl;
            else if (val[i].IsObject()) {
                std::cout << "Object" << std::endl;
                inspectJsonValue(val[i], indent + 4);
            }
            else if (val[i].IsArray()) {
                std::cout << "Array" << std::endl;
                inspectJsonValue(val[i], indent + 4);
            }
            else std::cout << "Other" << std::endl;
        }
        if (val.Size() > 5)
            std::cout << indentStr << "  ... and more elements" << std::endl;
    }
    else {
        std::cout << indentStr << "Primitive type: ";
        if (val.IsString()) std::cout << "String, Value: " << val.GetString() << std::endl;
        else if (val.IsInt()) std::cout << "Int, Value: " << val.GetInt() << std::endl;
        else if (val.IsDouble()) std::cout << "Double, Value: " << val.GetDouble() << std::endl;
        else if (val.IsBool()) std::cout << "Bool, Value: " << (val.GetBool() ? "true" : "false") << std::endl;
        else std::cout << "Unknown primitive" << std::endl;
    }
}

int main() {
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    const std::string filepath = "../data/large-file.json";
    std::string jsonStr = readFile(filepath);

    if (jsonStr.empty()) {
        std::cerr << "Error: JSON file empty or read failed." << std::endl;
        return 1;
    }
    std::cout << "Read JSON length: " << jsonStr.size() << " characters" << std::endl;

    rapidjson::Document doc;
    doc.Parse(jsonStr.c_str());

    if (doc.HasParseError()) {
        std::cerr << "Parse error: " << doc.GetParseError()
            << " (offset " << doc.GetErrorOffset() << ")" << std::endl;
        return 1;
    }

    std::cout << "Inspecting JSON structure:" << std::endl;
    inspectJsonValue(doc);

    return 0;
}
