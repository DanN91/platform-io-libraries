/*
    Adapted from https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce
*/

#include "PushButton.h"

namespace
{
    constexpr const uint16_t DEBOUNCE_DELAY_MS = 50;
    constexpr const uint16_t HELD_THRESHOLD_MS = 2000;
} // anonymous

PushButton::PushButton(uint8_t pin, uint8_t MAX_OBSERVERS_COUNT)
    : IObservable(MAX_OBSERVERS_COUNT), m_pin(pin)
{
}

void PushButton::Initialize() const
{
    pinMode(m_pin, INPUT_PULLUP);
}

void PushButton::HandleEvents()
{
    volatile bool reading = digitalRead(m_pin);
    // state changed due to noise or pressing?
    if (reading != m_lastState)
    {
        m_lastDebounceTime = millis();
    }

    // state did not change, or has not enough time has passed to take it into account
    if (((millis() - m_lastDebounceTime) > DEBOUNCE_DELAY_MS))
    {
        if (reading != m_lastReading)
        {
            if (m_lastReading == LOW) // LOW -> HIGH
            {
                if ((millis() - m_lastPressedTime) >= HELD_THRESHOLD_MS)
                {
                    // Serial.println("BTN:Held");
                    Notify(ButtonState::Held);
                }
                else
                {
                    // Serial.println("BTN:Released");
                    Notify(ButtonState::Released);
                }
            }
            else // HIGH -> LOW
            {
                // Serial.println("BTN:Pressed");
                Notify(ButtonState::Pressed);
                m_lastPressedTime = millis();
            }

            m_lastReading = reading;
        }
    }

    m_lastState = reading;
}