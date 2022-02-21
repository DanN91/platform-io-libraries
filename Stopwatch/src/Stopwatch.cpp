/*
    Stopwatch: track time in milliseconds or seconds.
    Author: Daniel Nistor
    License: MIT
*/

#include "Stopwatch.h"

void Stopwatch::Start()
{
    m_startedAtMs = millis();
}

void Stopwatch::Stop()
{
    m_stoppedAtMs = millis();
}

bool Stopwatch::IsRunning() const
{
    return m_startedAtMs > m_stoppedAtMs;
}

uint32_t Stopwatch::DurationMs() const
{
    return (m_stoppedAtMs < m_startedAtMs) ? 0 : (m_stoppedAtMs - m_startedAtMs);
}

uint32_t Stopwatch::DurationSec() const
{
    return DurationMs() / 1000;
}