#pragma once

#include <Arduino.h>

enum class TimerEvent : uint8_t
{
    Second = 1, // once a second
    Minute = 2, // once 60 seconds
    Hour = 4, // once 60 minutes
    Day = 8, // once 24h
    Week = 16, // once 7 days
    Month = 32 // once 4 weeks
};

inline bool operator ! (TimerEvent value)
{
    return value == static_cast<TimerEvent>(0);
}

inline TimerEvent operator | (TimerEvent lhs, TimerEvent rhs)
{
    return static_cast<TimerEvent>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
}

inline TimerEvent operator & (TimerEvent lhs, TimerEvent rhs)
{
    return static_cast<TimerEvent>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
}