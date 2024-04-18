#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Data {
    int key;
    string value;
};

string serializeToCSV(const vector<Data>& data) {
    stringstream ss;
    for (const auto& d : data) {
        ss << d.key << "," << d.value << "\n";
    }
    return ss.str();
}

void writeToCSV(const vector<Data>& data, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "Key,Value\n"; // Записываем заголовок
        for (const auto& d : data) {
            file << d.key << "," << d.value << "\n";
        }
        file.close();
        cout << "Data has been written to " << filename << endl;
    }
    else {
        cerr << "Unable to open file " << filename << " for writing." << endl;
    }
}

int main() {
    vector<Data> data = {
        {1, "One"},
        {2, "Two"},
        {3, "Three"},
        {4, "Four"},
        {5, "Five"}
    };

    string serializedData = serializeToCSV(data);
    cout << "Serialized Data:\n" << serializedData << endl;

    writeToCSV(data, "data.csv");

    return 0;
}
