#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>
#include <string>

using namespace std;

vector<vector<string>> parseData(string data) {
    vector<vector<string>> parsedData;

    bool freeSpace = true;
    int id = 0;

    for (int i = 0; i < data.size(); i++) {
        freeSpace = !freeSpace;
        int currentNumber = stoi(data.substr(i, 1));
        if (currentNumber == 0) continue;
        if (!freeSpace) {
            parsedData.push_back(vector<string>());
            for (int j = 0; j < currentNumber; j++) {
                parsedData[parsedData.size() - 1].push_back(to_string(id));
            }
            id++;
        }else {
            parsedData.push_back(vector<string>());
            for (int j = 0; j < currentNumber; j++) {
                parsedData[parsedData.size() - 1].emplace_back(".");
            }
        }
    }

    return parsedData;
}

vector<vector<string>> sortData(vector<vector<string>> parsedData) {

    for (int i = parsedData.size() - 1; i >= 0; i--) {
        if (parsedData[i][0] == ".") continue;
        for (int j = 0; j < i - 1; j++) {
            if (parsedData[j][0] == "." && parsedData[j].size() >= parsedData[i].size()) {

                vector<string> lastItems;
                for (int k = parsedData[i].size(); k < parsedData[j].size(); k++) {
                    lastItems.push_back(parsedData[j][k]);
                }

                parsedData[j] = parsedData[i];
                for (int k = 0; k < parsedData[i].size(); k++) {
                    parsedData[i][k] = ".";
                }
                if (lastItems.size() > 0 ) parsedData.insert(parsedData.begin() + j + 1, lastItems);
                break;
            }
        }
    }

    return parsedData;
}

long long getChecksum(vector<vector<string>> sortedData) {
    long long checksum = 0;
    int index = 0;
    for (int i = 0; i < sortedData.size(); i++) {
        for (int j = 0; j < sortedData[i].size(); j++) {
            if (sortedData[i][j] == ".") {
                index++;
                continue;
            }
            checksum += index * stoi(sortedData[i][j]);
            index++;
        }
    }

    return checksum;
}

int main() {

    fstream inputFile;
    inputFile.open("input.txt", ios::in);

    string data;
    getline(inputFile, data);

    vector<vector<string>> parsedData = parseData(data);
    vector<vector<string>> sorted = sortData(parsedData);
    cout << getChecksum(sorted) << endl;
    /*for (int i = 0; i < sorted.size(); i++) {
        for (int j = 0; j < sorted[i].size(); j++) {
            cout << sorted[i][j];
        }
    }*/


    return 0;
}