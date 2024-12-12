#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

struct Vec2i {
    int x;
    int y;

    Vec2i operator-(Vec2i& other) const {
        return {this->x - other.x, this->y - other.y};
    }

    Vec2i operator+(Vec2i other) const {
        return {this->x + other.x, this->y + other.y};
    }

    bool operator==(Vec2i& other) {
        return other.x == this->x && other.y == this->y;
    }

    bool operator<(const Vec2i& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

ostream& operator<<(ostream& os, const Vec2i v) {
    os << "[" << v.x << ", " << v.y << "]";
    return os;
}

struct Plot {
    set<Vec2i> neighbourhood;
    int perimeter;
    int corners;

    bool operator<(const Plot& other) const {
        return this->neighbourhood < other.neighbourhood; // Can have the same perimeter but not the same neighbourhood/group
    }
};

void traverseNeighbourhood(const vector<string>& garden, const Vec2i& position, set<Vec2i>& neighbourhood, int& perimeter, set<Vec2i>& visited) {

    visited.insert(position);
    neighbourhood.insert(position);
    perimeter += 4;

    Vec2i directions[] = {
        {0, 1}, // UP
        {0, -1}, // DOWN
        {1, 0}, // RIGHT
        {-1, 0} // LEFT
    };

    for (auto dir : directions) {
        Vec2i nextPosition = position + dir;
        if (nextPosition.x < 0 || nextPosition.x >= garden[0].size() ||
            nextPosition.y < 0 || nextPosition.y >= garden.size()) continue;
        if (garden[nextPosition.y][nextPosition.x] == garden[position.y][position.x]) {
            perimeter--;
            if (neighbourhood.find(nextPosition) != neighbourhood.end()) continue;
            traverseNeighbourhood(garden, nextPosition, neighbourhood, perimeter, visited);
        }
    }
}

int countCorners(const set<Vec2i>& points) {
    int cornerCount = 0;

    return cornerCount;
}

set<Plot> getPlots(vector<string> garden) {
    set<Plot> plots;
    set<Vec2i> visited;

    for (int y = 0; y < garden.size(); y++) {
        for (int x = 0; x < garden[0].size(); x++) {
            if (visited.find({x, y}) != visited.end()) continue; // Important for small runtime
            set<Vec2i> neighbourhood;
            int perimeter = 0;
            traverseNeighbourhood(garden, {x, y}, neighbourhood, perimeter, visited);
            int corners = countCorners(neighbourhood);
            plots.insert({neighbourhood, perimeter, corners});
        }
    }

    return plots;
}

int getSoluionPart1(const vector<string>& garden) {
    set<Plot> plots = getPlots(garden);
    int result = 0;
    for (auto plot : plots) {
        result += plot.neighbourhood.size() * plot.perimeter;
    }
    return result;
}

int getSoluionPart2(const vector<string>& garden) {
    set<Plot> plots = getPlots(garden);
    int result = 0;
    for (auto plot : plots) {
        result += plot.neighbourhood.size() * plot.corners;
    }
    return result;
}

int main() {

    // --- File ---
    fstream inputFile;
    inputFile.open("input.in", ios::in);
    // --- ---- ---

    std::vector<string> garden;

    // Parse data
    string line;
    while (getline(inputFile, line)) {
        garden.push_back(line);
    }

    
    
    auto s1p1 = std::chrono::high_resolution_clock::now();
    cout << "Solution Part 1: " << getSoluionPart1(garden) << endl;
    auto s2p1 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( s2p1 - s1p1 ).count();
    cout << "Executed in " << duration << "ms" << endl;
    
    auto s1p2 = std::chrono::high_resolution_clock::now();
    cout << "Solution Part 2: " << getSoluionPart2(garden) << endl;
    auto s2p2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>( s2p1 - s1p2 ).count();
    cout << "Executed in " << duration << "ms" << endl;

    return 0;
}
