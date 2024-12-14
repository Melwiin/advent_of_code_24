#pragma once

#include <ostream>
#include <iostream>

struct Vec2i {
    int x;
    int y;

    bool inRange(const Vec2i& rangeX, const Vec2i& rangeY) {
      return x >= rangeX.x && x <= rangeX.y && y >= rangeY.x && y <= rangeY.y;
    }

    Vec2i operator-(const Vec2i& other) const {
        return {this->x - other.x, this->y - other.y};
    }

    Vec2i operator+(const Vec2i& other) const {
        return {this->x + other.x, this->y + other.y};
    }

    bool operator==(const Vec2i& other) const {
        return other.x == this->x && other.y == this->y;
    }
    
    bool operator!=(const Vec2i& other) const {
      return !(*this == other);
    }

    bool operator<(const Vec2i& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    
    Vec2i operator%(const Vec2i& mod) {
      return {x % mod.x, y % mod.y};
    }
};

inline std::ostream& operator<<(std::ostream& os, const Vec2i& vec) {
  return os << "[" << vec.x << ", " << vec.y << "]";
}