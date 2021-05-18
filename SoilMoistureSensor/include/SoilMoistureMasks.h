#pragma once

#include <Arduino.h>

enum class SoilMoistureEvent
{
    MoistureChanged
};

inline SoilMoistureEvent operator |(SoilMoistureEvent lhs, SoilMoistureEvent rhs)
{
    return static_cast<SoilMoistureEvent>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
}

inline SoilMoistureEvent operator &(SoilMoistureEvent lhs, SoilMoistureEvent rhs)
{
    return static_cast<SoilMoistureEvent>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
}
