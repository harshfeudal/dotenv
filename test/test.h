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

        auto duration = end - start;
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

        size_t envValueSize;
        char* envValue;
        errno_t error = _dupenv_s(&envValue, &envValueSize, name.c_str());

        if (error == 0 && envValue != nullptr) {
            std::cout << name << " = " << envValue << std::endl;
            free(envValue);
        }
        else {
            std::cerr << name << " not found in environment" << std::endl;
        }
    }
    std::cout << std::endl;
}
