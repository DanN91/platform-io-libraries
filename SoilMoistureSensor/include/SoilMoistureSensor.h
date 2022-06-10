/*
    SoilMoistureSensor: Simple interface over one-analog-pin soil moisture sensor hardware using Observer.
    Author: Daniel Nistor
    MIT License, 2021
*/
#pragma once

#include <Arduino.h>

#include <ObserverPattern.h>
#include "SoilMoistureMasks.h"

class SoilMoistureSensor final : public IObservable<SoilMoistureEvent>
{
public:
    enum class Sensitivity : uint8_t
    {
        Low = 30,
        Medium = 10,
        High = 3
    };

    SoilMoistureSensor(uint8_t analogPin, Sensitivity sensitivity);
    virtual ~SoilMoistureSensor() = default;

    void HandleEvents();
    uint8_t Value() const;
    uint16_t RawValue() const;

    // non-copyable & non-movable
    SoilMoistureSensor(const SoilMoistureSensor&) = delete;
    SoilMoistureSensor& operator=(const SoilMoistureSensor&) = delete;
    SoilMoistureSensor(SoilMoistureSensor&&) = delete;
    SoilMoistureSensor& operator=(SoilMoistureSensor&&) = delete;

private:
    const uint8_t m_pin;
    uint16_t m_value = 0;
    const Sensitivity m_threshold = Sensitivity::Medium;
};