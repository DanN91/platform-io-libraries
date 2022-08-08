#pragma once

#include <Arduino.h>

enum class SleepMask : uint8_t
{
    None = 0,
    AllUnusedPinsLow = 1, // make sure Initialize() is called before any pinMode() call
    DisableBOD = 2,
    DisableADC = 4,
    UseInterrupt0 = 8, // D2
    UseInterrupt1 = 16, // D3
};

inline bool operator ! (SleepMask value)
{
  return value == static_cast<SleepMask>(0);
}

inline SleepMask operator | (SleepMask lhs, SleepMask rhs)
{
    return static_cast<SleepMask>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
}

inline SleepMask operator & (SleepMask lhs, SleepMask rhs)
{
    return static_cast<SleepMask>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
}