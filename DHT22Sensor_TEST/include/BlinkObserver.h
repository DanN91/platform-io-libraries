#pragma once

#include <Arduino.h>
#include <IObserver.h>

class BlinkObserver final : public IObserver
{
public:
    // lowerPin: 
    BlinkObserver(ISubject& subject, uint8_t lowerPin, uint8_t inRangePin, uint8_t greaterPin);

    void Initialize() const;

    // IObserver
    void Update(uint16_t mask, float newValue) override;

private:
    static void BlinkLED(byte ledPin);
    static void BlinkERROR(byte lower, byte inRange, byte higher);

    const uint8_t m_lowerPin;
    const uint8_t m_inRangePin;
    const uint8_t m_higherPin;
}; 