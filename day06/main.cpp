//
// Created by Melwin Kramer on 06/12/2024.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Vec2 {
  int x;
  int y;

  bool operator==(const Vec2 &other) const {
    return x == other.x && y == other.y;
  }
};

class SetVec2 {
public:
  SetVec2() { }

  void push_back(const Vec2& element) {
    for (auto e : data) {
      if (e.x == element.x && e.y == element.y) {
        return;
      }
    }
    data.push_back(element);
  }

  int size() {
    return data.size();
  }

  Vec2 operator[](const int index) const {
    return data[index];
  }
private:
    std::vector<Vec2> data;
};

SetVec2 getUniquePath(std::vector<std::string> map, const Vec2& guardPos) {
  SetVec2 path = SetVec2();

  Vec2 currentPos = guardPos;
  Vec2 direction = { 0, -1};

  path.push_back(guardPos);

  while (true) {
    Vec2 nextPos = { currentPos.x + direction.x, currentPos.y + direction.y };
    if (nextPos.x == map[0].size() || nextPos.y == map.size()) {
      break;
    }
    if (map[nextPos.y][nextPos.x] == '#') {
      // Rotate 90 deg
      const int newX = -direction.y;
      const int newY = direction.x;
      direction = { newX, newY };
    }else {
      currentPos = nextPos;
      map[nextPos.y][nextPos.x] = 'X';
      path.push_back(currentPos);
    }
  }

  return path;
}

SetVec2 getPossibleObstacles(std::vector<std::string> map, const Vec2& guardPos) {
  SetVec2 obstacles = SetVec2();

  SetVec2 path = getUniquePath(map, guardPos);
  Vec2 lastPos = path[1];

  for (int i = 2; i < path.size(); i++) {
    Vec2 currentObstacle = path[i - 1];
    Vec2 direction = { path[i].x - lastPos.x, path[i].y - lastPos.y };

    Vec2 currentPosition = path[i];
    Vec2 currentDiretion = direction;
    std::cout << "Dir: " << currentDiretion.x << ", " << currentDiretion.y << std::endl;
    while (true) {
      Vec2 nextPos = { currentPosition.x + currentDiretion.x, currentPosition.y + currentDiretion.y };
      if (nextPos.x >= map[0].size() || nextPos.y >= map.size() || nextPos.x < 0 || nextPos.y < 0) {
        break;
      }
      if (map[nextPos.y][nextPos.x] == '#' || nextPos == currentObstacle) {
        const int newX = -currentDiretion.y;
        const int newY = currentDiretion.x;
        currentDiretion = { newX, newY };
      }else {
        currentPosition = nextPos;
        if (currentPosition == path[i] && currentDiretion == direction) {
          obstacles.push_back(currentObstacle);
          break;
        }
      }
    }

    lastPos = path[i];
  }

  return obstacles;
}

int main() {

  std::vector<std::string> map;
  Vec2 guardPos = {-1, -1};

  std::fstream inputFile;
  inputFile.open("input.txt", std::ios::in);

  int lineCounter = 0;

  while (!inputFile.eof()) {
    std::string line;
    std::getline(inputFile, line);
    for (int i = 0; i < line.size(); i++) {
      if (line[i] == '^') {
        guardPos.x = i;
        guardPos.y = lineCounter;
      }
    }
    map.push_back(line);
    lineCounter++;
  }

  if (guardPos.x == -1 || guardPos.y == -1) {
    std::cerr << "Guard Position Error" << std::endl;
    return -1;
  }

  std::cout << getUniquePath(map, guardPos).size() << std::endl;
  std::cout << getPossibleObstacles(map, guardPos).size() << std::endl;

  return 0;
}
