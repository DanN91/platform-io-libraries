#include "BlinkObserver.h"

#include <DHT22Sensor.h>

BlinkObserver::BlinkObserver(ISubject& subject, uint8_t lowerPin, uint8_t inRangePin, uint8_t greaterPin)
    : IObserver(subject, DHT22Mask::Humidity)
    , m_lowerPin(lowerPin)
    , m_inRangePin(inRangePin)
    , m_higherPin(greaterPin)
{
}

void BlinkObserver::Initialize() const
{
    pinMode(m_lowerPin, OUTPUT);
    pinMode(m_inRangePin, OUTPUT);
    pinMode(m_higherPin, OUTPUT);
}

void BlinkObserver::Update(uint16_t mask, float newValue)
{
    if (mask & DHT22Mask::Humidity)
    {
        if (newValue >= 10 && newValue <= 40)
        {
            BlinkLED(m_lowerPin);
        }
        else if (newValue > 40 && newValue <= 60)
        {
            BlinkLED(m_inRangePin);
        }
        else if (newValue > 60 && newValue <= 100)
        {
            BlinkLED(m_higherPin);
        }
        else
        {
            BlinkERROR(m_lowerPin, m_inRangePin, m_higherPin);
        }
    }
}

void BlinkObserver::BlinkERROR(byte lower, byte inRange, byte higher)
{
    digitalWrite(lower, HIGH);
    digitalWrite(inRange, HIGH);
    digitalWrite(higher, HIGH);

    delay(2000);

    digitalWrite(lower, LOW);
    digitalWrite(inRange, LOW);
    digitalWrite(higher, LOW);

    delay(2000);
}

void BlinkObserver::BlinkLED(byte ledPin)
{
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    delay(1000);
}