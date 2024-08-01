#pragma once

#include <Arduino.h>

enum class AM2320SensorMask : uint8_t
{
    Temperature = 1,
    Humidity = 2,
};

inline AM2320SensorMask operator |(AM2320SensorMask lhs, AM2320SensorMask rhs)
{
    return static_cast<AM2320SensorMask>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
}

inline AM2320SensorMask operator &(AM2320SensorMask lhs, AM2320SensorMask rhs)
{
    return static_cast<AM2320SensorMask>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
}