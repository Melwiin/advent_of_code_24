#include <fstream>
#include <iostream>
#include <ostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

struct Vec2i {
  long long x;
  long long y;
  
  Vec2i operator+(const long long& factor) const {
    return { this->x + factor, this->y + factor };
  }
};

struct ClawMachine {
  Vec2i buttonA, buttonB;
  Vec2i prize;
};

ostream &operator<<(ostream &os, const Vec2i &vec) {
  return os << "[" << vec.x << ", " << vec.y << "]";
}

long long findCheapestWay(ClawMachine cm, const bool& part2 = false) {
  if (part2) {
    cm.prize = cm.prize + 10000000000000;
  }
  long long x1 = cm.buttonB.x * cm.prize.y - cm.buttonB.y * cm.prize.x;
  long long x2 = cm.buttonA.x * cm.buttonB.y - cm.buttonA.y * cm.buttonB.x;
  long long y1 = cm.prize.x * cm.buttonA.y - cm.prize.y * cm.buttonA.x;
  long long y2 = cm.buttonA.x * cm.buttonB.y - cm.buttonA.y * cm.buttonB.x;

  long long resX = -(x1 / x2), resY = -(y1 / y2);
  if (!part2 && (resX >= 100 || resY >= 100)) return 0;
  if (resX * cm.buttonA.x + resY * cm.buttonB.x == cm.prize.x &&
      resX * cm.buttonA.y + resY * cm.buttonB.y == cm.prize.y) {
        return resX * 3 + resY;
      }
      
      return 0;
}

int main() {

  vector<ClawMachine> clawMachines;

  fstream inputFile;
  inputFile.open("input.in", ios::in);

  string line;
  int lineCounter = 0;
  while (getline(inputFile, line)) {
    vector<long long> numbers;
    smatch match;
    while (regex_search(line, match, regex("(\\d+)"))) {
      numbers.push_back(stoll(match[1])) ;
      line = match.suffix().str();
    }

    if (lineCounter % 4 == 0) {
      clawMachines.push_back({});
      clawMachines.back().buttonA = {numbers[0], numbers[1]};
    } else if (lineCounter % 4 == 1) {
      clawMachines.back().buttonB = {numbers[0], numbers[1]};
    } else if (lineCounter % 4 == 2) {
      clawMachines.back().prize = {numbers[0], numbers[1]};
    }

    lineCounter++;
  }

  long long result1 = 0, result2 = 0;
  for (auto clawMachine : clawMachines) {
    result1 += findCheapestWay(clawMachine);
    result2 += findCheapestWay(clawMachine, true);
  }
  cout << "Solution Part 1: " << result1 << endl;
  cout << "Solution Part 2: " << result2 << endl;
  
  return 0;
}