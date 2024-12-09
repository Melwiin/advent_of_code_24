#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct Vector2i {
    int x;
    int y; 

    Vector2i operator-(Vector2i& other) const {
        return {this->x - other.x, this->y - other.y};
    }

    Vector2i operator+(Vector2i& other) const {
        return {this->x + other.x, this->y + other.y};
    }

    bool operator==(Vector2i& other) {
        return other.x == this->x && other.y == this->y;
    }

    bool operator<(const Vector2i& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

int findAntinodes(vector<string> data, const map<char, vector<Vector2i>>& sattelites, bool part2 = false) {
    set<Vector2i> antinodes;

    int mapSizeX = data[0].size();
    int mapSizeY = data.size();

    for (auto c : sattelites) {
        for (int s1 = 0; s1 < c.second.size() - 1; s1++) {
            for (int s2 = s1 + 1; s2 < c.second.size(); s2++) {
                Vector2i difference = c.second[s2] - c.second[s1];
                Vector2i newAntinode1 = part2 ? c.second[s1] : c.second[s1] - difference;
                Vector2i newAntinode2 = part2 ? c.second[s2] : c.second[s2] + difference;

                while (newAntinode1.x >= 0 && newAntinode1.x < mapSizeX && newAntinode1.y >= 0 && newAntinode1.y < mapSizeY) {
                    antinodes.insert(newAntinode1);
                    newAntinode1 = newAntinode1 - difference;
                    if (!part2) break;
                }

                while (newAntinode2.x >= 0 && newAntinode2.x < mapSizeX && newAntinode2.y >= 0 && newAntinode2.y < mapSizeY) {
                    antinodes.insert(newAntinode2);
                    newAntinode2 = newAntinode2 + difference;
                    if (!part2) break;
                }
            }
        }
    }

    return antinodes.size();
}

int main(int argc, char const *argv[])
{
    vector<string> data;
    map<char, vector<Vector2i>> sattelites;

    fstream inputFile;
    inputFile.open("input.txt", ios::in);

    int lineCounter = 0;
    while(!inputFile.eof()) {
        string line;
        getline(inputFile, line);

        for (int i = 0; i < line.size(); i++) {
            if (line[i] != '.') {
                auto sattelite = sattelites.find(line[i]);
                if (sattelite != sattelites.end())
                    sattelite->second.push_back({i, lineCounter});
                else
                    sattelites[line[i]] = vector<Vector2i>({{i, lineCounter}});
            }
        }

        data.push_back(line);
        lineCounter++;
    }

    cout << "Solution Part 1: " << findAntinodes(data, sattelites) << endl;
    cout << "Solution Part 2: " << findAntinodes(data, sattelites, true) << endl;


    return 0;
}
