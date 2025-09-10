#ifndef ETL_PROCESSOR_H
#define ETL_PROCESSOR_H

#include "rapidjson/document.h"

// Function to process the JSON events document for ETL
void processEvents(const rapidjson::Document& doc);

#endif // ETL_PROCESSOR_H
