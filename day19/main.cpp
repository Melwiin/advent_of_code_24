#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "../shared/Timer.hpp"

using namespace std;

map<string, size_t> patternCache;

inline std::string trim(const std::string &str) {
  auto start = std::find_if_not(str.begin(), str.end(), ::isspace);
  auto end = std::find_if_not(str.rbegin(), str.rend(), ::isspace).base();
  return (start < end) ? std::string(start, end) : "";
}

bool isPossible(const string &design, const set<string> &towels) {
  if (design.empty())
    return true;

  string part1 = design, rest = "";
  while (!part1.empty()) {
    // cout << "Part:" << part1 << " Rest:" << rest << endl;
    if (towels.find(part1) != towels.end()) {
      if (isPossible(rest, towels)) {
        return true;
      }
    }
    part1 = design.substr(0, part1.size() - 1);
    rest = design.substr(part1.size(), design.size());
  }

  return false;
}

size_t getVariationAmount(const string &design, const set<string> &towels) {
  if (patternCache.find(design) != patternCache.end())
    return patternCache[design];

  size_t result = 0;
  for (auto towel : towels) {
    if (design == towel) {
      result++;
      continue;
    }

    if (towel.length() > design.length())
      continue;

    if (design.substr(0, towel.length()) == towel) {
      result += getVariationAmount(design.substr(towel.length()), towels);
    }
  }

  if (patternCache.find(design) == patternCache.end())
    patternCache[design] = result;
  
  return result;
}

size_t getSolutionPart1(const vector<string> &designs,
                        const set<string> &towels) {
  size_t result = 0;
  for (auto design : designs) {
    result += isPossible(design, towels) ? 1 : 0;
  }
  return result;
}

size_t getSolutionPart2(const vector<string> &designs,
                        const set<string> &towels) {
  size_t result = 0;
  for (auto design : designs) {
    size_t options = getVariationAmount(design, towels);
    //cout << design << ": " << options << endl;
    result += options;
  }
  return result;
}

int main() {

  fstream inputFile("./day19/input.in");
  string line;

  set<string> towels;
  vector<string> designs;

  // Parse towels
  while (getline(inputFile, line)) {
    if (line.empty())
      break;
    stringstream lineStream(line);
    string towel;
    while (getline(lineStream, towel, ',')) {
      towels.insert(trim(towel));
    }
  }

  while (getline(inputFile, line)) {
    designs.push_back(line);
  }

  Timer timer;
  timer.start();
  cout << "Solution Part 1: " << getSolutionPart1(designs, towels) << " in "
       << timer.reset() << "ms" << endl;
  cout << "Solution Part 2: " << getSolutionPart2(designs, towels) << " in "
       << timer.reset() << "ms" << endl;

  return 0;
}