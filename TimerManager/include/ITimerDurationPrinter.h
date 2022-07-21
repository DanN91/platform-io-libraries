#pragma once

#include <Arduino.h>

struct TimerDuration
{
    TimerDuration(uint32_t seconds)
    {
        // Serial.print("Seconds: ");
        // Serial.println(seconds);
        // transform seconds into days:hours:minutes:seconds
        uint32_t tmpSeconds = seconds;
        m_days = tmpSeconds / (60 * 60 * 24);
        tmpSeconds %= (60 * 60 * 24);
        m_hours = tmpSeconds / (60 * 60);
        tmpSeconds %= (60 * 60);
        m_minutes = tmpSeconds / 60;
        tmpSeconds %= 60;
        m_seconds = tmpSeconds;
    }

    uint32_t toSeconds() const
    {
        return m_seconds + (m_minutes * 60) + (m_hours * 3600) + (m_days * 3600 * 24);
    }

    uint8_t m_days = 0;
    uint8_t m_hours = 0;
    uint8_t m_minutes = 0;
    uint8_t m_seconds = 0;
};

class ITimerDurationPrinter
{
public:
    virtual void print(const TimerDuration& duration) const = 0;
};