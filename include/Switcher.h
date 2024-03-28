#pragma once

#include <Arduino.h>

#include "ISwitch.h"

class Switcher final : public ISwitch
{
public:
    Switcher(uint8_t pin, bool useLowLevel = false);
    ~Switcher() = default;

    void Initialize();

    // ISwitch
    void On() override;
    void Off() override;

    // non-copyable & non-movable
    Switcher(const Switcher&) = delete;
    Switcher& operator=(const Switcher&) = delete;
    Switcher(Switcher&&) = delete;
    Switcher& operator=(Switcher&&) = delete;

private:
    const uint8_t m_switchPin;
};