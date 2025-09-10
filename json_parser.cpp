#include <iostream>
#include "json_parser.h"
#include "rapidjson/document.h"

void inspectJsonStructure(const rapidjson::Document& doc) {
    // Print info to explore unknown structure (keys, value types, etc.)
    if (doc.IsArray() && !doc.Empty() && doc[0].IsObject()) {
        std::cout << "Keys in first element:" << std::endl;
        const auto& firstItem = doc[0];
        for (auto itr = firstItem.MemberBegin(); itr != firstItem.MemberEnd(); ++itr) {
            std::cout << " - " << itr->name.GetString() << std::endl;
        }
    }
}
