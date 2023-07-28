/*
    LEDBlinkConfigurationComposite: Configuration for non-blocking blinking multiple LEDs.
    Author: Daniel Nistor
    MIT License, 2023
*/
#pragma once

#include <Arduino.h>
#include <Vector.h>

#include "ILEDBlinkConfiguration.h"

class LEDBlinkConfigurationComposite final : public ILEDBlinkConfiguration
{
public:
    LEDBlinkConfigurationComposite() = default;
    virtual ~LEDBlinkConfigurationComposite() = default;

    // ILEDBlinkConfiguration
    virtual void Activate() override;
    virtual void OnRun(ILEDToggler& toggler) override; // expects a toggler for all added configurations, so use LEDControllerComposite
    virtual bool HasFinished() const override;
    virtual void Reset() override;

    // Vector
    void Add(ILEDBlinkConfiguration* configuration);
    void Remove(ILEDBlinkConfiguration* configuration);

    // non-copyable & non-movable
    LEDBlinkConfigurationComposite(const LEDBlinkConfigurationComposite&) = delete;
    LEDBlinkConfigurationComposite& operator=(const LEDBlinkConfigurationComposite&) = delete;
    LEDBlinkConfigurationComposite(LEDBlinkConfigurationComposite&&) = delete;
    LEDBlinkConfigurationComposite& operator=(LEDBlinkConfigurationComposite&&) = delete;

private:
    ILEDBlinkConfiguration* GetCurrentConfiguration() const;

    uint8_t m_currentIndex = 0;
    Vector<ILEDBlinkConfiguration*> m_configurations;
};