//
// Created by Melwin Kramer on 05/12/2024.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Rule {
  int num1;
  int num2;
};

std::vector<std::string> split(const std::string& s, const std::string& delimiter) {
  size_t pos_start = 0, pos_end;
  const size_t delim_len = delimiter.length();
  std::vector<std::string> res;

  while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
    std::string token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back (token);
  }

  res.push_back (s.substr (pos_start));
  return res;
}

int checkUpdate(const std::vector<int> &update, const std::vector<Rule> &rules) {
  for (int i = 0; i < update.size(); i++) {
    for (auto [num1, num2] : rules) {
      if (num1 == update[i]) {
        for (int j = i - 1; j >= 0; j--) {
          if (update[j] == num2) {
            return 0;
          }
        }
      }
    }
  }
  return update[(update.size() - 1) / 2];
}

int sortUpdate(std::vector<int> &update, const std::vector<Rule> &rules) {
  for (int i = 0; i < update.size(); i++) {
    for (auto [num1, num2] : rules) {
      if (num1 == update[i]) {
        for (int j = i - 1; j >= 0; j--) {
          if (update[j] == num2) {
            // Handle Error
            update[j] = num1;
            update[i] = num2;
          }
        }
      }
    }
  }

  return checkUpdate(update, rules) == 0 ? sortUpdate(update, rules) : update[(update.size() - 1) / 2];
}

int main(int argc, const char * argv[]) {

  // DATA
  std::vector<Rule> rules;
  std::vector<std::vector<int>> updates;

  std::fstream inputFile;
  inputFile.open("input.txt", std::ios::in);

  if (!inputFile.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    return -1;
  }

  std::string line;
  while (!inputFile.eof()) {
    getline(inputFile, line);

    if (line.empty())
      break;

    Rule rule = { std::stoi(std::string({line[0], line[1]})) , std::stoi(std::string({line[3], line[4]})) };
    rules.push_back(rule);
  }

  while (!inputFile.eof()) {
    getline(inputFile, line);

    std::vector<int> update;
    for (std::string num : split(line, ",")) {
      update.push_back(std::stoi(num));
    }
    updates.push_back(update);
  }

  int result1 = 0;
  for (const auto& update : updates) {
    result1 += checkUpdate(update, rules);
  }
  std::cout << "Solution Part 1: " << result1 << std::endl;

  int result2 = 0;
  for (auto& update : updates) {
    if (checkUpdate(update, rules) == 0) {
      result2 += sortUpdate(update, rules);
    }
  }
  std::cout << "Solution Part 2: " << result2 << std::endl;

  return 0;
}