/*
    SoilMoistureSensor: Simple interface over one-analog-pin soil moisture sensor hardware.
    Author: Daniel Nistor
    MIT License, 2021
*/

#pragma once

#include <Arduino.h>

class SoilMoistureSensor final
{
public:
    SoilMoistureSensor(uint8_t analogPin);
    ~SoilMoistureSensor() = default;

    uint8_t Value() const;

    // non-copyable & non-movable
    SoilMoistureSensor(const SoilMoistureSensor&) = delete;
    SoilMoistureSensor& operator=(const SoilMoistureSensor&) = delete;
    SoilMoistureSensor(SoilMoistureSensor&&) = delete;
    SoilMoistureSensor& operator=(SoilMoistureSensor&&) = delete;

private:
    const uint8_t m_pin;
};