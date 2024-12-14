#pragma once

#include <chrono>

using namespace std::chrono;

class Timer {
public:
    Timer() { };
    
    void start() {
       startTime = high_resolution_clock::now();
    };
    
    double reset() {
      double duration = stop().getDuration();
      startTime = high_resolution_clock::now();
      return duration;
    }
    
    Timer& stop() {
      endTime = high_resolution_clock::now();
      return *this;
    };
    
    double getDuration() {
      return duration_cast<microseconds>(endTime - startTime).count() / 1000.0;
    }
private:
  time_point<std::chrono::system_clock, duration<long, std::ratio<1, 1000000000>>> startTime;
  time_point<std::chrono::system_clock, duration<long, std::ratio<1, 1000000000>>> endTime;
};