#pragma once

#include <Arduino.h>

enum class DHT22Mask : uint8_t
{
    Temperature = 1,
    Humidity = 2,
};

inline DHT22Mask operator |(DHT22Mask lhs, DHT22Mask rhs)
{
    return static_cast<DHT22Mask>(static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
}

inline DHT22Mask operator &(DHT22Mask lhs, DHT22Mask rhs)
{
    return static_cast<DHT22Mask>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
}