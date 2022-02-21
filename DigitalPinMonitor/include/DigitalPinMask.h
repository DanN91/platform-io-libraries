#pragma once

#include <Arduino.h>

enum class DigitalState : uint8_t
{
    Low = 1,
    High = 2
};

inline DigitalState operator |(DigitalState lhs, DigitalState rhs)
{
    return static_cast<DigitalState>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
}

inline DigitalState operator &(DigitalState lhs, DigitalState rhs)
{
    return static_cast<DigitalState>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
}