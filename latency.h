#pragma once
#ifndef LATENCY_MODULE_H
#define LATENCY_MODULE_H

#include <chrono>
#include <string>

class LatencyModule {
public:
    // Start a timer and return the start time
    static std::chrono::high_resolution_clock::time_point start();

    // End the timer and log the latency
    static void end(const std::chrono::high_resolution_clock::time_point& start_time, const std::string& operation_name);

private:
    // Private constructor to prevent instantiation (static-only class)
    LatencyModule() = delete;
};

#endif // LATENCY_MODULE_H