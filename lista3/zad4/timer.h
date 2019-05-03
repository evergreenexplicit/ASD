#ifndef TIMER_H
#define TIMER_H

#include <chrono>

struct Timer
{
    using Clock = std::chrono::high_resolution_clock;
    using Duration = std::chrono::duration<double, std::ratio<1, 1000>>;
    using Timepoint = std::chrono::time_point<Clock>;

    static const Timepoint
    start()
    {
        return Clock::now();
    }

    static const double
    stop(Timepoint t)
    {
        return std::chrono::duration_cast<Duration>(Clock::now() - t).count();
    }
};

#endif