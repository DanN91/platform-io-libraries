/*
    ILEDBlinkConfiguration: Interface for non-blocking blinking of one or multiple LED(s) using Composite pattern.
    Author: Daniel Nistor
    MIT License, 2023
*/
#pragma once

#include <Arduino.h>

class ILEDToggler
{
public:
    ILEDToggler() = default;
    virtual ~ILEDToggler() = default;

    virtual bool Toggle() = 0; // returns the state of the LED(s): HIGH or LOW
};

class ILEDBlinkConfiguration
{
public:
    ILEDBlinkConfiguration() = default;
    ILEDBlinkConfiguration(uint32_t intervalMs);
    ILEDBlinkConfiguration(uint32_t intervalMs, uint8_t times);
    virtual ~ILEDBlinkConfiguration() = default;

    virtual void Activate() = 0;
    virtual void OnRun(ILEDToggler& toggler) = 0;
    virtual bool HasFinished() const = 0;
    virtual void Reset() = 0;

protected:
    uint32_t m_intervalMs = 0;
    uint8_t m_times = 1;
    uint8_t m_countTimes = 0;
    uint32_t m_lastMs = 0;
};