/*
    Adapted from https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce
*/

#pragma once

#include "PushButtonMasks.h"

#include <ObserverPattern.h>

class PushButton final : public IObservable<ButtonState>
{
public:
    PushButton(uint8_t pin, uint8_t MAX_OBSERVERS_COUNT = 1);
    ~PushButton() = default;

    void Initialize() const;

    void HandleEvents();

private:
    const uint8_t m_pin;

    uint32_t m_lastDebounceTime = 0;
    uint32_t m_lastPressedTime = 0;

    bool m_lastReading = true; // the last value read via digitalRead
    bool m_lastState = true; // the last state after debouncing the value read from digitalRead
};