#include <Arduino.h>

#include "TogglePushButton.h"

// the debounce time; increase if the output flickers
constexpr const uint8_t DEBOUNCE_DELAY = 50;

TogglePushButton::TogglePushButton(uint8_t pin, IPushButtonObserver& observer)
    : m_pin(pin)
    , m_observer(observer)
{
    // nothing more
}

void TogglePushButton::Initialize() const
{
    pinMode(m_pin, INPUT);
}

void TogglePushButton::HandleEvents()
{
    static bool m_buttonState = false;
    static bool lastButtonState = false;
    static uint32_t lastDebounceTime = 0;

    const bool reading = digitalRead(m_pin);

    if (reading != lastButtonState)
        lastDebounceTime = millis();

    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY)
    {
        if (reading != m_buttonState)
        {
            m_buttonState = reading;

            if (m_buttonState == LOW)
                m_observer.WasPressed();
        }
    }

    lastButtonState = reading;
}
