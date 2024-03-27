#pragma once

#include <Arduino.h>

enum class Settings : uint8_t
{
    IncubationTemperature,
    IncubationHumidity,
    LockdownTemperature,
    LockdownHumidity,
    CycleState,
    ChangeStateDate,
    ChangeStateTime,
};

inline Settings operator |(Settings lhs, Settings rhs)
{
    return static_cast<Settings>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
}

inline Settings operator &(Settings lhs, Settings rhs)
{
    return static_cast<Settings>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
}