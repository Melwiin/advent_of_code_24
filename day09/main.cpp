#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>
#include <string>

using namespace std;

vector<string> formatData(string data) {
    int id = 0;
    bool freeSpace = false;
    vector<string> result;

    for (int i = 0; i < data.size(); i++) {
        int currentNumber = data[i] - '0';
        if (!freeSpace) {
            for (int n = 0; n < currentNumber; n++) {
                result.push_back(to_string(id));
            }
            id++;
        }else {
            for (int n = 0; n < currentNumber; n++) {
                result.push_back(".");
            }
        }
        freeSpace = !freeSpace;
    }
    return result;
}

vector<string> formatDataPart2(string data) {
    int id = 0;
    bool freeSpace = false;
    vector<string> result;

    for (int i = 0; i < data.size(); i++) {
        int currentNumber = data[i] - '0';
        if (!freeSpace) {
            string entry;
            for (int m = 0; m < currentNumber; m++) {
                entry.append(to_string(id));
            }
            result.push_back(entry);

            id++;
        }else {
            string entry;
            for (int m = 0; m < currentNumber; m++) {
                entry.append(".");
            }
            if (!entry.empty()) result.push_back(entry);
        }
        freeSpace = !freeSpace;
    }
    return result;
}

vector<string> reinsertData(vector<string> data) {
    int j = data.size() - 1;
    for (int i = 0; i < data.size(); i++) {
        if ( j <= i) break;
        if (data[i] == ".") {
            if (data[j] == ".") {
                i--;
                j--;
                continue;
            }
            data[i] = data[j];
            data[j] = ".";
            j--;
        }
    }

    return data;
}

vector<string> reinsertDataPart2(vector<string> data) {
    for (int i = data.size() - 1; i >= 0; i--) {
        if (data[i][0] == '.') continue;
        //cout << data[i] << endl;
        for (int s = 0; s < i; s++) {
            if (data[s][0] == '.' && data[s].size() >= data[i].size()) {\
                int diff = data[s].size() - data[i].size();
                string entry;
                if (data[s].size() > data[i].size()) {

                    for (int m = 0; m < diff; m++) {
                        entry.append(".");
                    }
                }



                data[s] = data[i];
                string dots;
                for (auto c : data[i]) {
                    dots += '.';
                }
                data[i] = dots;

                if (!entry.empty()) data.insert(data.begin() + s + 1, entry);\



                break;
            }
        }


    }

    return data;
};

long long getChecksum(vector<string> data) {
    long long checksum = 0;
    for (int i = 0; i < data.size(); i++) {
        if (data[i] == ".") continue;
        checksum += i * stoll(data[i]);
    }
    return checksum;
}

long long getChecksumPart2(vector<string> data) {
    long long checksumData = 0;
    string e = accumulate(data.begin(), data.end(), std::string(""));

    for (int i = 0; i < e.size(); i++) {
        string entry;
        entry.push_back(e[i]);
        if (e[i] == '.') continue;
        checksumData += i * stoll(entry);
    }

    return checksumData;
}

int main(int argc, char const *argv[])
{

    string data;
    data.reserve(20000000);

    fstream inputFile;
    inputFile.open("input.txt", ios::in);

    getline(inputFile, data);

    // cout << data << endl;

    // cout << getChecksum(reinsertData(formatData(data))) << endl;

    auto res = reinsertDataPart2(formatDataPart2(data));
    /*for (auto r : res) {
        cout << r << " ";
    }*/
    cout << getChecksumPart2(res);

    return 0;
}
