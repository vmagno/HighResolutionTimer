#ifndef HIGHRESOLUTIONTIMER_H
#define HIGHRESOLUTIONTIMER_H

#include <chrono>
#include <cstdint>

namespace Util {

/**
 * @brief The HighResolutionTimer class. Provides a simple interface to start and stop a high-resolution timer and get
 * its average running time. Currently at microsecond resolution.
 */
class HighResolutionTimer
{
    typedef std::chrono::high_resolution_clock       Clock;
    typedef Clock::time_point                        Reading;
    typedef std::chrono::microseconds                Duration;
    typedef std::chrono::duration<float, std::milli> MsDuration;

public:
    HighResolutionTimer() : Start_(Clock::now()), Stop_(Clock::now()), Total_(0), Count_(0) {}

    inline void Reset()
    {
        Total_ = Duration::zero();
        Count_ = 0;
    }

    inline void Start()
    {
        Start_ = Clock::now();
        Count_++;
    }
    inline void Stop()
    {
        Stop_ = Clock::now();
        Total_ += std::chrono::duration_cast<Duration>(Stop_ - Start_);
    }

    inline float GetLastTimeMs() const { return std::chrono::duration_cast<MsDuration>(Stop_ - Start_).count(); }
    inline float GetAvgTimeMs() const
    {
        return static_cast<float>(std::chrono::duration_cast<MsDuration>(Total_).count()) / Count_;
    }

private:
    Reading  Start_;
    Reading  Stop_;
    Duration Total_;
    uint64_t Count_;
};

} // namespace Util

#endif // HIGHRESOLUTIONTIMER_H
