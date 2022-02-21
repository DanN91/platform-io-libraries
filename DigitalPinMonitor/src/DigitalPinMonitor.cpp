/*
    DigitalPinMonitor: monitor the state of a digital pin using observer as a pattern for notifying state changes.
    Author: Daniel Nistor
    License: MIT
*/

#include "DigitalPinMonitor.h"

namespace
{
    constexpr const uint16_t DEBOUNCE_DELAY_MS = 50;
} // anonymous

DigitalPinMonitor::DigitalPinMonitor(uint8_t pin, uint8_t MAX_OBSERVERS_COUNT)
    : IObservable(MAX_OBSERVERS_COUNT)
    , m_pin(pin)
{
}

void DigitalPinMonitor::Initialize() const
{
    pinMode(m_pin, INPUT);
}

void DigitalPinMonitor::HandleEvents()
{
    volatile bool reading = digitalRead(m_pin);

    if (reading != m_lastButtonState)
        m_lastDebounceTime = millis();

    if ((millis() - m_lastDebounceTime) > DEBOUNCE_DELAY_MS)
    {
        if (reading != m_lastReading)
        {
            m_lastReading = reading;
            if (m_lastReading == LOW) // High -> Low
            {
                // Serial.println("PIN:LOW");
                Notify(DigitalState::Low);
            }
            else // Low -> High
            {
                // Serial.println("PIN:HIGH");
                Notify(DigitalState::High);
            }
        }
    }

    m_lastButtonState = reading;
}