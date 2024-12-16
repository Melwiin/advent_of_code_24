#include <cstddef>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <set>

#include "../shared/Timer.hpp"
#include "../shared/Vec2i.hpp"

using namespace std;

const map<char, Vec2i> directions = {
  {'>', {1, 0}},
  {'<', {-1, 0}},
  {'v', {0, 1}},
  {'^', {0, -1}}
};

class Object {
public:
  Object(vector<Vec2i> _positions, bool _canMove) : positions(_positions), canMove(_canMove) { };

  vector<Vec2i> positions;
  Vec2i position;
  bool canMove;

  void print() {
    cout << "Object at ";
    for (auto pos : positions) {
      cout << pos;
    }
    cout << " can move " << (canMove ? "{Yes}" : "{No}") << endl;
  }
};

Object* findObject(Vec2i position, vector<Object>& objects) {
  for (auto &obj : objects) {
    for (auto pos : obj.positions) {
      if (pos == position) {
        return &obj;
      }
    }
  }

  return nullptr;
}

bool moveObject(Object& obj, const char& command, vector<Object>& objects, bool shouldMove = true) {
  if (!obj.canMove) return false;

  Vec2i direction = directions.at(command);

  set<Object*> neighbors;
  vector<Vec2i> nextPositions;
  for (auto position : obj.positions) {
    Vec2i next = position + direction;
    nextPositions.push_back(next);
  }

  if (command == '<') {
    auto neighbor = findObject(nextPositions[0], objects);
    if (neighbor == nullptr) cout << "stupid" << endl;
    else {
      // cout << neighbor->positions[0] << endl;
      neighbors.insert(neighbor);
    }
  }else if(command == '>') {
    int index = nextPositions.size() == 2 ? 1 : 0;
    auto neighbor = findObject(nextPositions[index], objects);
    if (neighbor == nullptr) cout << "stupid" << endl;
    else {
      neighbors.insert(neighbor);
    }
  }else {
    for (auto nextPosition : nextPositions) {
      auto neighbor = findObject(nextPosition, objects);
      if (neighbor != nullptr) neighbors.insert(neighbor);
    }
  }


  if (neighbors.size() == 0) {
    for (size_t i = 0; i < nextPositions.size(); i++) {
      if (shouldMove) obj.positions[i] = nextPositions[i];
    }
    return true;
  }else {
    // cout << "Check next" << endl;
    for (auto neighbor : neighbors) {
      // cout << neighbor->positions[0] << neighbor->positions[1] << endl;
      if (!moveObject(*neighbor, command, objects, false)) {
        return false;
      }
    }
    
    for (auto neighbor : neighbors) {
      if (!moveObject(*neighbor, command, objects, true)) {
        return false;
      }
    }

    for (size_t i = 0; i < nextPositions.size(); i++) {
      if (shouldMove) obj.positions[i] = nextPositions[i];
    }
    return true;
  }

  return false;
}


void printField(const Object& robot, const vector<Object>& objects) {
  for (int y = 0; y < 10; y++) {
    for (int x = 0; x < 20; x++) {
      bool found = false;
      for (auto position : robot.positions) {
        if (position == Vec2i{x, y}) {
          cout << "@";
          found = true;
        }
      }
      if (found) continue;
      for (auto object : objects) {
        for (size_t i = 0; i < object.positions.size(); i++) {
          if (object.positions[i] == Vec2i{x, y}) {
            if (object.canMove) {
              cout << (i == 0 ? "[" : "]");
              found = true;
              break;
            }else {
              cout << "#";
              found = true;
              break;
            }
          }
        }
      }
      if (!found) cout << ".";
    }
    cout << endl;
  }
}

vector<Object> executeCommands(Object robot, vector<Object> objects, const vector<string>& commands) {
  printField(robot, objects);
  for (auto commandline : commands) {
    for (auto command : commandline) {
      cout << "Command: " << command << endl;
      moveObject(robot, command, objects);
      printField(robot, objects);
      cout << endl;
    }
  }
  return objects;
}

int calculateGPS(const vector<Object>& objects) {
  int gps = 0;
  for (auto object : objects) {
    if (!object.canMove) continue;
    gps += 100 * object.positions[0].y + object.positions[0].x;
  }
  return gps;
}

int main() {

  Object robot({}, true);
  vector<Object> objects; // walls and boxes
  vector<string> commands;

  fstream inputFile("./day15/input.in");
  string line;

  // Parse field
  int y = 0;
  while(getline(inputFile, line)) {
    if (line.empty()) break;

    int x = 0;
    for (auto c : line) {
      if (c == '#') {
        objects.push_back({{{x, y}}, false});
        objects.push_back({{{x+1, y}}, false});
      }else if (c == 'O') {
        objects.push_back({{{x, y}, {x + 1, y}}, true});
      }else if (c == '@') {
        robot.positions = {{x, y}};
      }
      x += 2;
    }
    y++;
  }

  // Parse commands
  while (getline(inputFile, line)) {
    commands.push_back(line);
  }

  Timer timer;
  timer.start();
  auto movedObjects = executeCommands(robot, objects, commands);
  cout << "Solution Part 1: " << calculateGPS(movedObjects) << " in " << timer.reset() << "ms" << endl;

  return 0;
}