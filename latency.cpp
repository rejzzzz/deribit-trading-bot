#include "latency.h"
#include <iostream>
#include <chrono>
#include <iomanip> // For formatting output

// Start a timer and return the current high-resolution clock time
std::chrono::high_resolution_clock::time_point LatencyModule::start()
{
    return std::chrono::high_resolution_clock::now();
}

// End the timer, calculate the elapsed time, and log the latency
void LatencyModule::end(const std::chrono::high_resolution_clock::time_point &start_time, const std::string &operation_name)
{
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    // Log the latency with precision
    std::cout << "[" << operation_name << "] Latency: "
              << std::fixed << std::setprecision(3) << (duration / 1000.0) << " ms" << std::endl;
}