/*
    LEDControllerComposite: Simple interface for blinking more LEDs as a batch.
    Author: Daniel Nistor
    MIT License, 2023
*/
#pragma once

#include <Arduino.h>

#include <Vector.h>
#include "ILEDController.h"

class LEDControllerComposite final : public ILEDController
{
public:
    LEDControllerComposite() = default;
    virtual ~LEDControllerComposite() = default;

    // ILEDController
    virtual void Initialize() override;
    virtual void Configure(ILEDBlinkConfiguration* configuration) override;
    virtual bool HasFinished() const override;
    virtual explicit operator bool() const override;

    // Vector
    void Add(ILEDController *const led);
    void Remove(ILEDController *const led);

    // non-copyable & non-movable
    LEDControllerComposite(const LEDControllerComposite&) = delete;
    LEDControllerComposite& operator=(const LEDControllerComposite&) = delete;
    LEDControllerComposite(LEDControllerComposite&&) = delete;
    LEDControllerComposite& operator=(LEDControllerComposite&&) = delete;

private:
    virtual void Run() override;

    Vector<ILEDController*> m_leds;
};
