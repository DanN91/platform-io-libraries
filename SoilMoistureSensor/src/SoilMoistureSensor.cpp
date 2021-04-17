/*
    SoilMoistureSensor: Simple interface over one-analog-pin soil moisture sensor hardware.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "SoilMoistureSensor.h"

namespace
{
    constexpr const uint16_t AIR_VALUE = 596;
    constexpr const uint16_t WATER_VALUE = 260;
} // anonymous

SoilMoistureSensor::SoilMoistureSensor(uint8_t analogPin)
    : m_pin(analogPin)
{
}

uint8_t SoilMoistureSensor::Value() const
{
    const uint8_t moisturePercent = map(analogRead(m_pin), AIR_VALUE, WATER_VALUE, 0, 100);
    return (moisturePercent >= 100) ? 100 : moisturePercent;
}