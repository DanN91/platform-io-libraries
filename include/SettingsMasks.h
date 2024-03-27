#pragma once

#include <Arduino.h>

enum class Settings : uint8_t
{
	TemperatureMin = 1,
	TemperatureMax = 2,
	HumidityMin = 4,
	HumidityMax = 8,
};

inline Settings operator |(Settings lhs, Settings rhs)
{
    return static_cast<Settings>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
}

inline Settings operator &(Settings lhs, Settings rhs)
{
    return static_cast<Settings>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
}