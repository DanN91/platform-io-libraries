/*
    SoilMoistureSensor: Simple interface over one-analog-pin soil moisture sensor hardware using Observer.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "SoilMoistureSensor.h"

namespace
{
    constexpr const uint16_t DRY_VALUE = 586;
    constexpr const uint16_t WET_VALUE = 350;
} // anonymous

SoilMoistureSensor::SoilMoistureSensor(uint8_t analogPin, Sensitivity sensitivity)
    : IObservable(1)
    , m_pin(analogPin)
    , m_threshold(sensitivity)
{
}

void SoilMoistureSensor::HandleEvents()
{
    const auto Difference = [](uint16_t valueOne, uint16_t valueTwo){ return (valueOne >= valueTwo) ? (valueOne - valueTwo) : (valueTwo - valueOne); };

    if (const auto currentValue = Value(); Difference(currentValue, m_value) >= static_cast<uint8_t>(m_threshold))
    {
        m_value = currentValue;
        Notify(SoilMoistureEvent::MoistureChanged);
    }
}

uint8_t SoilMoistureSensor::Value() const
{
    return constrain(map(analogRead(m_pin), DRY_VALUE, WET_VALUE, 0, 100), 0, 100);
}

uint16_t SoilMoistureSensor::RawValue() const
{
    return analogRead(m_pin);
}
