#include "Timer.h"
#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::Start()
{
    m_Start = std::chrono::steady_clock::now();
}

std::string Timer::Stop()
{
    m_End = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = m_End - m_Start;

    auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
    duration -= hours;
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    duration -= minutes;
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    duration -= seconds;
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

    std::ostringstream formattedTime;
    formattedTime << std::setfill('0') << std::setw(2) << hours.count() << ":"
                  << std::setw(2) << minutes.count() << ":"
                  << std::setw(2) << seconds.count() << "."
                  << std::setw(3) << milliseconds.count();

    return formattedTime.str();
}
