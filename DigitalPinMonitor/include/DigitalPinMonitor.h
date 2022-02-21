/*
    DigitalPinMonitor: monitor the state of a digital pin using observer as a pattern for notifying state changes.
    Author: Daniel Nistor
    License: MIT
*/

#include "DigitalPinMask.h"

#include <ObserverPattern.h>

class DigitalPinMonitor final : public IObservable<DigitalState>
{
public:
    DigitalPinMonitor(uint8_t pin, uint8_t MAX_OBSERVERS_COUNT = 1);
    ~DigitalPinMonitor() = default;

    void Initialize() const;

    void HandleEvents();

private:
    const uint8_t m_pin;

    uint32_t m_lastDebounceTime = millis();
    bool m_lastReading = false;
    bool m_lastButtonState = false;
};