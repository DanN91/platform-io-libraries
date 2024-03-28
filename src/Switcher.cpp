#include "Switcher.h"

Switcher::Switcher(uint8_t pin, bool useLowLevel)
    : ISwitch()
    , m_switchPin(pin)
    , m_useLowLevel(useLowLevel)
{
}

void Switcher::Initialize()
{
    pinMode(m_switchPin, OUTPUT);
    Off();
}

void Switcher::On()
{
    if (!m_isSwitchOn)
    {
        digitalWrite(m_switchPin, m_useLowLevel ? LOW : HIGH);
        m_isSwitchOn = m_useLowLevel ? !digitalRead(m_switchPin) : digitalRead(m_switchPin);
    }
}

void Switcher::Off()
{
    if (m_isSwitchOn)
    {
        digitalWrite(m_switchPin, m_useLowLevel ? HIGH : LOW);
        m_isSwitchOn = m_useLowLevel ? !digitalRead(m_switchPin) : digitalRead(m_switchPin);
    }
}