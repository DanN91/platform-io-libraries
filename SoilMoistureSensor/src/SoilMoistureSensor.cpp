/*
    SoilMoistureSensor: Simple interface over one-analog-pin soil moisture sensor hardware using Observer.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "SoilMoistureSensor.h"

namespace
{
    constexpr const uint16_t AIR_VALUE = 684;
    constexpr const uint16_t WATER_VALUE = 350;
} // anonymous

SoilMoistureSensor::SoilMoistureSensor(uint8_t analogPin, Sensitivity sensitivity)
    : IObservable(1)
    , m_pin(analogPin)
    , m_threshold(static_cast<uint8_t>(sensitivity))
{
}

void SoilMoistureSensor::HandleEvents()
{
    const auto Difference = [](uint16_t valueOne, uint16_t valueTwo){ return (valueOne >= valueTwo) ? (valueOne - valueTwo) : (valueTwo - valueOne); };

    if (const auto currentValue = Value(); Difference(currentValue, m_value) >= m_threshold)
    {
        m_value = currentValue;
        Notify(SoilMoistureEvent::MoistureChanged);
    }
}

uint8_t SoilMoistureSensor::Value() const
{
    return constrain(map(analogRead(m_pin), AIR_VALUE, WATER_VALUE, 0, 100), 0, 100);
}