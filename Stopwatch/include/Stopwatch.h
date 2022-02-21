/*
    Stopwatch: track time in milliseconds or seconds.
    Author: Daniel Nistor
    License: MIT
*/

#pragma once

#include <Arduino.h>

class Stopwatch final
{
public:
    Stopwatch() = default;
    ~Stopwatch() = default;

    // State
    void Start();
    void Stop();
    bool IsRunning() const;

    // Duration
    uint32_t DurationMs() const;
    uint32_t DurationSec() const;

    // non-movable & non-copyable
    Stopwatch(Stopwatch&&) = delete;
    Stopwatch& operator=(Stopwatch&&) = delete;
    Stopwatch(const Stopwatch&) = delete;
    Stopwatch& operator=(const Stopwatch&) = delete;

private:
    uint32_t m_stoppedAtMs = 0;
    uint32_t m_startedAtMs = 0;
};