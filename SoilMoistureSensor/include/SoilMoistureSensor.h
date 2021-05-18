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
    enum class Sensitivity
    {
        Low = 30,
        Medium = 10,
        High = 3
    };

    SoilMoistureSensor(uint8_t analogPin, Sensitivity sensitivity);
    ~SoilMoistureSensor() = default;

    void HandleEvents();
    uint8_t Value() const;

    // non-copyable & non-movable
    SoilMoistureSensor(const SoilMoistureSensor&) = delete;
    SoilMoistureSensor& operator=(const SoilMoistureSensor&) = delete;
    SoilMoistureSensor(SoilMoistureSensor&&) = delete;
    SoilMoistureSensor& operator=(SoilMoistureSensor&&) = delete;

private:
    const uint8_t m_pin;
    uint16_t m_value = 0;
    const uint8_t m_threshold = 0;
};