#pragma once

#include <chrono>
#include <iostream>
#include <iomanip>

class Clock {
public:
    Clock() { start(); }
    void start();
    double stop();

private:
    std::chrono::steady_clock mClock;
    std::chrono::time_point<std::chrono::steady_clock> begin;
    std::chrono::time_point<std::chrono::steady_clock> end;
};

void Clock::start() {
    begin = mClock.now();
    return;
}

double Clock::stop() {
    end = mClock.now();
    std::chrono::duration<double, std::micro> mic = end - begin;
    return mic.count();
}
