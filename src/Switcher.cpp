#include "Switcher.h"

Switcher::Switcher(uint8_t pin, bool useLowLevel)
    : ISwitch(useLowLevel)
    , m_switchPin(pin)
{
}

void Switcher::Initialize()
{
    pinMode(m_switchPin, OUTPUT);
    Off();
}

void Switcher::On()
{
    digitalWrite(m_switchPin, m_useLowLevel ? LOW : HIGH);
    ISwitch::On();
}

void Switcher::Off()
{
    digitalWrite(m_switchPin, m_useLowLevel ? HIGH : LOW);
    ISwitch::Off();
}