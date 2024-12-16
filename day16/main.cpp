#include <climits>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>

#include "../shared/Timer.hpp"
#include "../shared/Vec2i.hpp"


using namespace std;

int MAZE_WIDTH, MAZE_HEIGHT;

enum DIRECTION { EAST, SOUTH, WEST, NORTH };

const Vec2i directions[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

struct Reindeer {
  Vec2i position;
  DIRECTION direction;
};

void printMaze(const Reindeer &reindeer, const Vec2i &finishPos,
               const set<Vec2i> &walls) {

  for (int y = 0; y < MAZE_HEIGHT; y++) {
    for (int x = 0; x < MAZE_WIDTH; x++) {
      Vec2i currentPos{x, y};

      // Move the cursor to the current position
      cout << "\033[" << (y + 1) << ";" << (x + 1) << "H";

      if (reindeer.position == currentPos) {
        cout << "@"; // Print the reindeer
      } else if (finishPos == currentPos) {
        cout << "F"; // Print the finish position
      } else if (walls.find(currentPos) != walls.end()) {
        cout << "#"; // Print a wall
      } else {
        cout << " "; // Print an empty space
      }
    }
  }
  cout.flush(); // Ensure everything is printed immediately

}

DIRECTION turnClockwise(DIRECTION direction) {
  if (direction == NORTH)
    return EAST;
  if (direction == EAST)
    return SOUTH;
  if (direction == SOUTH)
    return WEST;
  return NORTH;
}

DIRECTION turnCounter(DIRECTION direction) {
  if (direction == NORTH)
    return WEST;
  if (direction == EAST)
    return NORTH;
  if (direction == SOUTH)
    return EAST;
  return SOUTH;
}

struct State {
  Vec2i position;
  int direction;
  int score;
  int heuristic;

  bool operator<(const State &other) const {
    return score + heuristic > other.score + other.heuristic; // Min-heap
  }
};

int heuristic(const Vec2i &a, const Vec2i &b) {
  return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

int findShortestPathAStar(const Reindeer &reindeer, const Vec2i &finishPos,
                          const set<Vec2i> &walls) {
  std::priority_queue<State> pq;
  std::map<std::tuple<Vec2i, int>, int> visited;

  pq.push({reindeer.position, reindeer.direction, 0, heuristic(reindeer.position, finishPos)});
  visited[{reindeer.position, reindeer.direction}] = 0;

  while (!pq.empty()) {
    State curr = pq.top();
    pq.pop();

    if (curr.position == finishPos)
      return curr.score;

    for (int i = 0; i < 4; i++) {
      Vec2i nextPosition = curr.position + directions[i];
      if (walls.find(nextPosition) != walls.end())
        continue;

      int minimalTurns =
          directions[i] == directions[curr.direction] ? 0
          : directions[i] == directions[turnCounter((DIRECTION)curr.direction)] ||
                  directions[i] == directions[turnClockwise((DIRECTION)curr.direction)]
              ? 1
              : 2;

      int newScore = curr.score + 1 + (minimalTurns * 1000);

      auto stateKey = std::make_tuple(nextPosition, i);
      if (!visited.count(stateKey) || visited[stateKey] > newScore) {
        visited[stateKey] = newScore;
        pq.push({nextPosition, i, newScore, heuristic(nextPosition, finishPos)});
      }
    }
  }

  return INT_MAX;
}

int main() {

  set<Vec2i> walls;
  Vec2i finishPos;
  Reindeer reindeer;

  fstream inputFile("./day16/input.in");
  string line;

  int y = 0;
  while (getline(inputFile, line)) {
    for (int x = 0; x < (int)line.size(); x++) {
      if (line[x] == '#')
        walls.insert({x, y});
      else if (line[x] == 'S') {
        reindeer.position = Vec2i{x, y};
        reindeer.direction = EAST;
      } else if (line[x] == 'E') {
        finishPos = Vec2i{x, y};
      }
    }
    MAZE_WIDTH = line.size();
    y++;
  }
  MAZE_HEIGHT = y;

  // printMaze(reindeer, finishPos, walls);
  Timer timer;
  timer.start();
  cout << findShortestPathAStar(reindeer, finishPos, walls) << " in " << timer.reset() << "ms" << endl;

  return 0;
}