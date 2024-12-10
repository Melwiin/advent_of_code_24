#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Vector2i {
    int x;
    int y;

    Vector2i operator-(const Vector2i& other) const {
        return {this->x - other.x, this->y - other.y};
    }

    Vector2i operator+(const Vector2i& other) const {
        return {this->x + other.x, this->y + other.y};
    }

    bool operator==(const Vector2i& other) const {
        return other.x == this->x && other.y == this->y;
    }

    bool operator<(const Vector2i& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

bool isWithinBounds(const vector<vector<int>>& map, int x, int y) {
    return x >= 0 && y >= 0 && x < map[0].size() && y < map.size();
}

void traverseMap(const vector<vector<int>>& map, const Vector2i currentPosition, vector<Vector2i>& nineHeightPositions, bool part2) {
    const int currentValue = map[currentPosition.y][currentPosition.x];

    if (currentValue == 9) {
        if (!part2) // Remove duplicates
            for (auto n : nineHeightPositions)
                if (n == currentPosition) return;

        nineHeightPositions.push_back(currentPosition);
        return;
    }

    Vector2i directions[] = {
        {currentPosition.x - 1, currentPosition.y}, // Up
        {currentPosition.x + 1, currentPosition.y}, // Down
        {currentPosition.x, currentPosition.y - 1}, // Left
        {currentPosition.x, currentPosition.y + 1}  // Right
    };

    for (const auto& direction : directions) {
        if (isWithinBounds(map, direction.x, direction.y)) {
            if (map[direction.y][direction.x] == currentValue + 1)
                traverseMap(map, direction, nineHeightPositions, part2);
        }
    }
}

size_t getTrialheadScore(const vector<vector<int>>& topographicMap, Vector2i startPosition, vector<Vector2i> nineHeightPositions = {}, bool part2 = false) {
    traverseMap(topographicMap, startPosition, nineHeightPositions, part2);
    return nineHeightPositions.size();
}

int main() {

    fstream inputFile;
    inputFile.open("input.txt", ios::in);

    vector<vector<int>> topographicMap;
    vector<Vector2i> trialheads;

    while (!inputFile.eof()) {
        string line;
        getline(inputFile, line);
        topographicMap.push_back(vector<int>());
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == '0') {
                trialheads.push_back(Vector2i({i, (int)topographicMap.size() - 1}));
            }
            topographicMap.back().push_back(line[i] - '0');
        }

    }

    size_t result1 = 0, result2 = 0;

    for (auto trialhead : trialheads) {
        result1 += getTrialheadScore(topographicMap, trialhead);
    }

    for (auto trialhead : trialheads) {
        result2 += getTrialheadScore(topographicMap, trialhead, {}, true);
    }

    cout << "Solution Part 1: " << result1 << endl;
    cout << "Solution Part 2: " << result2 << endl;

    return 0;
}