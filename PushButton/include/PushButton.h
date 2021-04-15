/*
    ...
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

    uint32_t m_lastDebounceTime = millis();
    uint32_t m_lastPressedTime = millis();
    bool m_lastReading = false;
    bool m_lastButtonState = false;
};