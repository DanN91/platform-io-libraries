/*
    SoilMoistureSensor: Simple interface over one-analog-pin soil moisture sensor hardware.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "SoilMoistureSensor.h"

namespace
{
    constexpr const uint16_t AIR_VALUE = 684;
    constexpr const uint16_t WATER_VALUE = 350;
} // anonymous

SoilMoistureSensor::SoilMoistureSensor(uint8_t analogPin)
    : m_pin(analogPin)
{
}

uint8_t SoilMoistureSensor::Value() const
{
    return constrain(map(analogRead(m_pin), AIR_VALUE, WATER_VALUE, 0, 100), 0, 100);
}