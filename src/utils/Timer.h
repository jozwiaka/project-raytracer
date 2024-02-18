#pragma once
#include <string>
#include <chrono>

class Timer
{
public:
    Timer();
    ~Timer();
    void Start();
    std::string Stop();

private:
    std::chrono::time_point<std::chrono::steady_clock> m_Start, m_End;
};
