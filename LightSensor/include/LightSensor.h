/*
    LightSensor: Simple interface over one LDR hardware using Observer to notify light intensity changes.
    Author: Daniel Nistor
    MIT License, 2021
*/
#pragma once

#include <Arduino.h>
#include <ObserverPattern.h>

#include "LightSensorMasks.h"

class LightSensor final : public IObservable<LightSensorEvent>
{
public:
    enum class Sensitivity
    {
        Low = 200,
        Medium = 100,
        High = 50
    };

    LightSensor(uint8_t analogPin, Sensitivity sensitivity);
    ~LightSensor() = default;

    void HandleEvents();
    uint16_t Value() const;

    // non-copyable & non-movable
    LightSensor(const LightSensor&) = delete;
    LightSensor& operator=(const LightSensor&) = delete;
    LightSensor(LightSensor&&) = delete;
    LightSensor& operator=(LightSensor&&) = delete;

private:
    const uint8_t m_pin;
    uint16_t m_value = 0;
    const uint16_t m_threshold = 0;
};
