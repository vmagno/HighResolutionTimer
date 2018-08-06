#ifndef HIGHRESOLUTIONTIMER_H
#define HIGHRESOLUTIONTIMER_H

#include <chrono>
#include <cstdint>

namespace Util {

/**
 * @brief Provides a simple interface to start and stop a high-resolution chronometer-like timer and get
 * its average running time, its last running time or the time elapsed since it was last started. Currently at
 * microsecond resolution.
 */
class HighResolutionTimer
{
    using Clock      = std::chrono::high_resolution_clock;
    using Duration   = std::chrono::microseconds; //!< Resolution of the clock
    using DurationMs = std::chrono::duration<float, std::milli>;
    using Reading    = Clock::time_point;

public:
    HighResolutionTimer()
        : Start_(Clock::now())
        , Stop_(Start_)
        , Total_(0)
        , Count_(0)
    {
    }

    inline void Reset()
    {
        Start_ = Clock::now();
        Stop_  = Start_;
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
        Total_ += getDuration<Duration>(Stop_ - Start_);
    }

    inline float GetLastTimeMs() const { return getNumTicks<DurationMs>(Stop_ - Start_); }
    inline float GetAvgTimeMs() const { return getNumTicks<DurationMs>(Total_) / Count_; }
    inline float GetTimeSinceLastStartMs() const { return getNumTicks<DurationMs>(Clock::now() - Start_); }

private:
    Reading  Start_;
    Reading  Stop_;
    Duration Total_; //!< Total time elapsed while this timer was running (not counting current, if still running)
    uint64_t Count_;

private: // functions
    template <class T, class U>
    static inline float getNumTicks(const U& interval)
    {
        return getDuration<T>(interval).count();
    }

    template <class T, class U>
    static inline T getDuration(const U& interval)
    {
        return std::chrono::duration_cast<T>(interval);
    }
};

} // namespace Util

#endif // HIGHRESOLUTIONTIMER_H
