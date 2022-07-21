#pragma once

#include <Arduino.h>

enum class TimerEvent : uint8_t
{
    Second, // once a second
    Minute, // once 60 seconds
    Hour, // once 60 minutes
    Day, // once 24h
    Week, // once 7 days
    Month // once 4 weeks
};

inline TimerEvent operator | (TimerEvent lhs, TimerEvent rhs)
{
    return static_cast<TimerEvent>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
}

inline TimerEvent operator & (TimerEvent lhs, TimerEvent rhs)
{
    return static_cast<TimerEvent>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
}