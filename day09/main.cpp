#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

string formatData(string data) {
    int id = 0;
    bool freeSpace = false;
    for (int i = 0; i < data.size(); i++) {
        if (!freeSpace) {
            int dataSpaces = int(data[i]) - int('0');
            string entry;
            for (int d = 0; d < dataSpaces; d++) {
                for (auto c : to_string(id)) {
                    entry.push_back(c);
                }
            }
            data.replace(i, 1, entry);
            id++;
            i += entry.size() - 1;
        }else{
            int emptySpaces = data[i] - '0';
            string entry;
            for (int d = 0; d < emptySpaces; d++) {
                entry.push_back('.');
            }
            data.replace(i, 1, entry);
            i += emptySpaces - 1;
        }
        freeSpace = !freeSpace;
        cout << data << endl;
    }

    return data;
}

int main(int argc, char const *argv[])
{

    string data;
    data.reserve(20000000);

    fstream inputFile;
    inputFile.open("input.txt", ios::in);

    getline(inputFile, data);

    // cout << data << endl;
    string res = formatData(data);

    return 0;
}
