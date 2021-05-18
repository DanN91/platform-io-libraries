/*
    LightSensor: Simple interface over one LDR hardware using Observer to notify light intensity changes.
    Author: Daniel Nistor
    MIT License, 2021
*/
#include "LightSensor.h"

LightSensor::LightSensor(uint8_t analogPin, Sensitivity sensitivity)
    : IObservable(1)
    , m_pin(analogPin)
    , m_threshold(static_cast<uint16_t>(sensitivity))
{
}

void LightSensor::HandleEvents()
{
    const auto Difference = [](uint16_t valueOne, uint16_t valueTwo){ return (valueOne >= valueTwo) ? (valueOne - valueTwo) : (valueTwo - valueOne); };

    if (const auto currentValue = Value(); Difference(currentValue, m_value) >= m_threshold)
    {
        m_value = currentValue;
        Notify(LightSensorEvent::IntensityChanged);
    }
}

uint16_t LightSensor::Value() const
{
    return analogRead(m_pin);
}
