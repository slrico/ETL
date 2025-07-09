#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "json.hpp" // Include the JSON library

using namespace std;
using json = nlohmann::json;

// Step 1: Read JSON Data
vector<int> readJsonData(const string& filename) {
    ifstream file(filename);
    json j;
    file >> j;
    
    vector<int> data = j.get<vector<int>>();  // Convert JSON array to vector<int>
    return data;
}

// Step 2: Process Data (sort)
vector<int> processData(vector<int>& data) {
    sort(data.begin(), data.end());
    return data;
}

// Step 3: Write JSON Data
void writeJsonData(const string& filename, const vector<int>& data) {
    json j = data;  // Convert vector to JSON array
    ofstream file(filename);
    file << j.dump(4);  // Pretty-print with 4 spaces indentation
}

int main() {
    string inputFile = "input.json";
    string outputFile = "output.json";

    vector<int> data = readJsonData(inputFile);
    data = processData(data);
    writeJsonData(outputFile, data);

    cout << "JSON data pipeline executed successfully!" << endl;
    return 0;
}