#pragma once
#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std::chrono;


class Logger{
public:
    Logger() = default;
    void Log(const std::string& message);
    void StartTimer(const std::string& operation_name);
    long long StopTimer();
    ~Logger() = default;
private:
    time_point<high_resolution_clock> start_time;
    std::string current_operation;
    std::string GetCurrentTime();
};