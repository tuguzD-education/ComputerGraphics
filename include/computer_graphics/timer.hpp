#pragma once

#ifndef TIMER_HPP_INCLUDED
#define TIMER_HPP_INCLUDED

#include <chrono>

namespace computer_graphics {

class Timer {
  public:
    using Clock = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;
    using Duration = Clock::duration;
    using FrameCount = std::uint16_t;

    explicit Timer() noexcept;
    explicit Timer(std::nullptr_t) noexcept;

    void Reset();
    void Tick();

    [[nodiscard]] float StartTime() const;

    [[nodiscard]] float DeltaTime() const;

    [[nodiscard]] float FramesPerSecond() const;

  private:
    explicit Timer(TimePoint time_point) noexcept;

    [[nodiscard]] float SecondsFromCurrent(TimePoint time_point) const;
    [[nodiscard]] static float SecondsFrom(Duration duration);

    TimePoint start_;
    TimePoint current_;
    TimePoint previous_;
    TimePoint previous_frame_;
    FrameCount frame_count_;
    float frames_per_second_;
};

}  // namespace computer_graphics

#endif  // TIMER_HPP_INCLUDED
