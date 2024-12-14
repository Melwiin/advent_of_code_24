#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>

#include "../shared/Vec2i.hpp"
#include "../shared/Timer.hpp"

using namespace std;

const int FIELD_WIDTH = 101;
const int FIELD_HEIGHT = 103;
const int SIM_SECONDS = 100;

enum QUADRANT {
  TOPLEFT,
  TOPRIGHT,
  BOTLEFT,
  BOTRIGHT,
  NONE
};

struct Robot {
  Vec2i pos;
  Vec2i velocity;
  QUADRANT currentQuadrant = NONE;

  void move(const int& dir = 1, const int& times = 1) {
    pos = (pos + velocity);
    if (pos.x < 0)
      pos = pos + Vec2i({FIELD_WIDTH, 0});
    if (pos.x >= FIELD_WIDTH)
      pos = pos - Vec2i({FIELD_WIDTH, 0});
    if (pos.y < 0)
        pos = pos + Vec2i({0, FIELD_HEIGHT});
    if (pos.y >= FIELD_HEIGHT)
        pos = pos - Vec2i({0, FIELD_HEIGHT});

    if (pos.inRange({0, (FIELD_WIDTH - 1) / 2 - 1}, {0, (FIELD_HEIGHT - 1) / 2 - 1})) {
      currentQuadrant = TOPLEFT;
    }else if (pos.inRange({(FIELD_WIDTH - 1) / 2 + 1, FIELD_WIDTH}, {0, (FIELD_HEIGHT - 1) / 2 - 1})) {
      currentQuadrant = TOPRIGHT;
    }else if (pos.inRange({(FIELD_WIDTH - 1) / 2 + 1, FIELD_WIDTH}, {(FIELD_HEIGHT - 1) / 2 + 1, FIELD_HEIGHT})) {
      currentQuadrant = BOTRIGHT;
    }else if (pos.inRange({0, (FIELD_WIDTH - 1) / 2 - 1}, {(FIELD_HEIGHT - 1) / 2 + 1, FIELD_HEIGHT})) {
      currentQuadrant = BOTLEFT;
    }else{
      currentQuadrant = NONE;
    }
  }
};

bool isRobot(vector<Robot> robots, Vec2i pos) {
  for (auto robot : robots) {
    if (robot.pos == pos) return true;
  }
  return false;
}

void renderRobots(const vector<Robot>& robots) {
  for (int y = 0; y < FIELD_HEIGHT; y++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      if (isRobot(robots, {x, y})) cout << "▓";
      else cout << "░";
    }
    cout << endl;
  }
}

int getSafetyFactor(vector<Robot> robots) {
  int amountQuadrants[5] = {};
  for (auto &robot : robots) {
    for (int i = 0; i < SIM_SECONDS; i++) robot.move();
    amountQuadrants[robot.currentQuadrant]++;
  }
  return amountQuadrants[TOPLEFT] * amountQuadrants[TOPRIGHT] * amountQuadrants[BOTLEFT] * amountQuadrants[BOTRIGHT];
}

int getEasterEgg(vector<Robot> robots) {
  int amountQuadrants[5] = {};
  int index = 0;
  int limit = robots.size() / 2;
  while(amountQuadrants[TOPLEFT] < limit && 
        amountQuadrants[TOPRIGHT] < limit && 
        amountQuadrants[BOTLEFT] < limit && 
        amountQuadrants[BOTRIGHT] < limit) 
  {
    amountQuadrants[0] = 0;
    amountQuadrants[1] = 0;
    amountQuadrants[2] = 0;
    amountQuadrants[3] = 0;
    amountQuadrants[4] = 0;
    
    for (auto &robot : robots) {
      robot.move();
      amountQuadrants[robot.currentQuadrant]++;
    }
    index++;
  }
  
  //renderRobots(robots);
  
  return index;
}



int main() {
  fstream inputFile("./day14/input.in", ios::in);
  string line;

  vector<Robot> robots;

  regex digits("(-\\d+)|(\\d+)");
  while (getline(inputFile, line)) {
    std::sregex_iterator begin(line.begin(), line.end(), digits), end;

    int values[4] = {};
    int index = 0;
    for (std::sregex_iterator i = begin; i != end && index < 4; ++i) {
        std::smatch match = *i;
        values[index++] = stoi(match.str());
    }
    
    robots.push_back({{values[0], values[1]}, {values[2], values[3]}});
  }
  
  Timer timer;
  
  timer.start();
  cout << "Solution Part 1: " << getSafetyFactor(robots) << " in " << timer.reset() << "ms" << endl;
  cout << "Solution Part 2: " << getEasterEgg(robots) << " in " << timer.stop().getDuration() << "ms"<< endl;
}