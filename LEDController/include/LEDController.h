/*
    LEDController: Simple interface over one or many LED hardware with non-blocking functionality.
    Author: Daniel Nistor
    MIT License, 2023
*/
#pragma once

#include <Arduino.h>

#include "ILEDController.h"

class LEDController final : public ILEDController, ILEDToggler
{
public:
    LEDController(uint8_t digitalPin);
    ~LEDController() = default;

    // ILEDController
    virtual void Initialize() override;
    virtual bool HasFinished() const override;
    virtual void Configure(ILEDBlinkConfiguration* configuration) override;
    virtual explicit operator bool() const override;

    // ILEDToggler
    virtual bool Toggle() override;

    // #FIXME:REMOVE
    void SetName(const char* name) { m_name = name; }

    // non-copyable & non-movable
    LEDController(const LEDController&) = delete;
    LEDController& operator=(const LEDController&) = delete;
    LEDController(LEDController&&) = delete;
    LEDController& operator=(LEDController&&) = delete;

private:
    virtual void Run();

    ILEDBlinkConfiguration* m_configuration = nullptr;

    const char* m_name = nullptr;
    const uint8_t m_pin;
    bool m_state = LOW;
};
