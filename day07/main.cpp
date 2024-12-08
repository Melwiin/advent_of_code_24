//
// Created by Melwin Kramer on 07/12/2024.
//

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

std::vector<std::string> split(const std::string& s, const std::string& delimiter) {
    size_t pos_start = 0, pos_end;
    const size_t delim_len = delimiter.length();
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        std::string token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

std::vector<std::string> generateCombinationsPart1(const size_t amount) {
    std::vector<std::string> combinations;
    const int totalCombinations = static_cast<int>(pow(2, amount));

    for (int i = 0; i < totalCombinations; ++i) {
        std::string combination;
        for (int j = 0; j < amount; ++j) {
            if (i & (1 << j)) {
                combination += '*';
            } else {
                combination += '+';
            }
        }
        combinations.push_back(combination);
    }

    return combinations;
}

std::vector<std::string> generateCombinationsPart2(const size_t amount) {
    std::vector<std::string> combinations;
    const int totalCombinations = static_cast<int>(pow(3, amount));

    for (int i = 0; i < totalCombinations; ++i) {
        std::string combination;
        int current = i;
        for (size_t j = 0; j < amount; ++j) {
            int remainder = current % 3;
            if (remainder == 0) {
                combination += '*';
            } else if (remainder == 1) {
                combination += '+';
            } else {
                combination += '|';
            }
            current /= 3;
        }
        combinations.push_back(combination);
    }

    return combinations;
}

long long int checkNumbersPart1(const long long int result, const vector<long long int> &numbers) {
    vector<string> combinations = generateCombinationsPart1(numbers.size());

    for (int i = 0; i < combinations.size(); ++i) {
        long long int new_result = numbers[0];
        for (int j = 1; j < numbers.size(); ++j) {
            if (combinations[i][j - 1] == '*') {
                new_result *= numbers[j];
            }else if (combinations[i][j - 1] == '+') {
                new_result += numbers[j];
            }
        }
        if (new_result == result) {
            return result;
        }
    }

    return 0;
}

long long int checkNumbersPart2(const long long int result, const vector<long long int> &numbers) {
    vector<string> combinations = generateCombinationsPart2(numbers.size());

    for (int i = 0; i < combinations.size(); ++i) {
        long long int new_result = numbers[0];
        for (int j = 1; j < numbers.size(); ++j) {
            if (combinations[i][j - 1] == '*') {
                new_result *= numbers[j];
            }else if (combinations[i][j - 1] == '+') {
                new_result += numbers[j];
            }else if (combinations[i][j - 1] == '|') {
                new_result = stoll(to_string(new_result) + to_string(numbers[j]));
            }
        }

        if (new_result == result) {
            return result;
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {

    vector<long long int> results;
    vector<vector<long long int>> numbersData;

    fstream inputFile;
    inputFile.open("input.txt", ios::in);
    while (!inputFile.eof()) {
        string line;
        getline(inputFile, line);
        long long int result = stoll(split(line, ":")[0]);
        vector<string> numbersString = split(split(line, ":")[1], " ");
        vector<long long int> numbers;
        for (const auto & i : numbersString) {
            if (i.empty()) continue;
            numbers.push_back(stoll(i));
        }
        results.push_back(result);
        numbersData.push_back(numbers);
    }

    unsigned long long result1 = 0;

    for (int i = 0; i < results.size(); ++i) {
        result1 += checkNumbersPart1(results[i], numbersData[i]);
    }

    cout << "Solution Part 1: " << result1 << endl;

    unsigned long long result2 = 0;

    for (int i = 0; i < results.size(); ++i) {
        result2 += checkNumbersPart2(results[i], numbersData[i]);
    }

    cout << "Solution Part 2: " << result2 << endl;

    return 0;
}
