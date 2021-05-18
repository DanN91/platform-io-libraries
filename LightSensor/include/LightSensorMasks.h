#pragma once

#include <Arduino.h>

enum class LightSensorEvent
{
    IntensityChanged
};

inline LightSensorEvent operator |(LightSensorEvent lhs, LightSensorEvent rhs)
{
    return static_cast<LightSensorEvent>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
}

inline LightSensorEvent operator &(LightSensorEvent lhs, LightSensorEvent rhs)
{
    return static_cast<LightSensorEvent>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
}
