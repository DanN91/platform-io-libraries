/*
    LightSensor: Simple interface over one LDR hardware using Observer to notify light intensity changes.
    Author: Daniel Nistor
    MIT License, 2021
*/
#include "LightSensor.h"

namespace
{
    constexpr const uint16_t BRIGHT_DAY_VALUE = 1000;
    constexpr const uint16_t DARK_NIGHT_VALUE = 10;
} // anonymous

LightSensor::LightSensor(uint8_t analogPin, Sensitivity sensitivity)
    : IObservable(1)
    , m_pin(analogPin)
    , m_threshold(static_cast<uint8_t>(sensitivity))
{
}

void LightSensor::HandleEvents()
{
    const auto Difference = [](uint8_t valueOne, uint8_t valueTwo){ return (valueOne >= valueTwo) ? (valueOne - valueTwo) : (valueTwo - valueOne); };

    if (const auto currentValue = Value(); Difference(currentValue, m_value) >= m_threshold)
    {
        m_value = currentValue;
        Notify(LightSensorEvent::IntensityChanged);
    }
}

uint16_t LightSensor::Value() const
{
    return constrain(map(analogRead(m_pin), DARK_NIGHT_VALUE, BRIGHT_DAY_VALUE, 0, 100), 0, 100);
}
