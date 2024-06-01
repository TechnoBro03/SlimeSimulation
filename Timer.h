#pragma once

#include <chrono>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;
    std::chrono::duration<double> duration;

public:
    // Constructor
    Timer() = default;

    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    void end() {
        end_time = std::chrono::high_resolution_clock::now();
        duration = end_time - start_time;
    }

    double get_millis() {
        std::chrono::duration<double, std::milli> millis = duration;
        return millis.count();
    }
};