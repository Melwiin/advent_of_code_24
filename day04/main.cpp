#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::string reverseString(std::string str) {
    std::reverse(str.begin(), str.end());
    return str;
}

int part1(const std::vector<std::string> &data) {
    long int result = 0;

    for (int y = 0; y < data.size(); y++) {
        for (int x = 0; x < data[0].size(); x++) {
            // Check to the right
            if (x < data[y].size() - 3) {
                std::string check = {data[y][x], data[y][x + 1], data[y][x + 2], data[y][x + 3]};
                if (check == "XMAS" || reverseString(check) == "XMAS") {
                    result++;
                }
            }
            // Check to the bottom
            if (y < data.size() - 3) {
                std::string check = {data[y][x], data[y + 1][x], data[y + 2][x], data[y + 3][x]};
                if (check == "XMAS" || reverseString(check) == "XMAS") {
                    result++;
                }
            }
            // Check right bottom diagonally
            if (y < data.size() - 3 && x < data[y].size() - 3) {
                std::string check = {data[y][x], data[y + 1][x + 1], data[y + 2][x + 2], data[y + 3][x + 3]};
                if (check == "XMAS" || reverseString(check) == "XMAS") {
                    result++;
                }
            }
            // Check left bottom diagonally
            if (y < data.size() - 3 && x >= 3) {
                std::string check = {data[y][x], data[y + 1][x - 1], data[y + 2][x - 2], data[y + 3][x - 3]};
                if (check == "XMAS" || reverseString(check) == "XMAS") {
                    result++;
                }
            }
        }
    }

    return result;
}

int part2(const std::vector<std::string> &data) {
    long int result = 0;

    for (int y = 0; y < data.size(); y++) {
        for (int x = 0; x < data[0].size(); x++) {
            if (x == 0 || y == 0 || x > data[0].size() - 2 || y > data.size() - 2) continue;
            // continue when on the edge -> no A possible
            if (data[y][x] == 'A') {
                std::string checkDiagonal1 = {data[y - 1][x - 1], data[y][x], data[y + 1][x + 1]};
                std::string checkDiagonal2 = {data[y - 1][x + 1], data[y][x], data[y + 1][x - 1]};

                if ((checkDiagonal1 == "MAS" || checkDiagonal1 == "SAM") &&
                    (checkDiagonal2 == "MAS" || checkDiagonal2 == "SAM")) { result++; } // Found X-MAS
            }
        }
    }

    return result;
}

int main() {
    std::ifstream inputFile;
    inputFile.open("input.txt");

    std::vector<std::string> data;

    if (inputFile.is_open()) {
        std::string line;
        while (!inputFile.eof()) {
            std::getline(inputFile, line);
            data.push_back(line);
        }
    }

    inputFile.close();

    std::cout << "Solution Part 1: " << part1(data) << std::endl;
    std::cout << "Solution Part 2: " << part2(data) << std::endl;

    return 0;
}
