#pragma once

#include <dotenv/dotenv.h>
#include <chrono>

class Timer
{
public:
    Timer() { m_StartTimepoint = std::chrono::high_resolution_clock::now(); }
    ~Timer() { Stop(); }

    void Stop() {
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

        auto   duration = end - start;
        double ms = duration * 0.001;

        std::cout << "-> " << duration << "us (" << ms << "ms)\n";
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
};

inline void run_test(const std::string& name) {
    std::cout << "* " << name << " test: " << std::endl;
    {
        Timer timer;
        const char* my_var = std::getenv((name).c_str());
        if (my_var) {
            std::cout << name << " = " << my_var << std::endl;
        }
        else {
            std::cerr << name << " not found in environment" << std::endl;
        }
    }
    std::cout << std::endl;
}
