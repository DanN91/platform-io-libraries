/*
    LEDBlinkConfiguration: Configuration for non-blocking blinking of an LED.
    Author: Daniel Nistor
    MIT License, 2023
*/
#pragma once

#include <Arduino.h>

#include "ILEDBlinkConfiguration.h"

class LEDBlinkConfiguration final : public ILEDBlinkConfiguration
{
public:
    LEDBlinkConfiguration(uint32_t intervalMs);
    LEDBlinkConfiguration(uint32_t intervalMs, uint8_t times);
    ~LEDBlinkConfiguration() = default;

    virtual void Activate() override;
    virtual void OnRun(ILEDToggler& toggler) override;
    virtual bool HasFinished() const override;
    virtual void Reset() override;
};