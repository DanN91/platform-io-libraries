/*
    LEDControllerComposite: Simple interface for blinking more LEDs as a batch.
    Author: Daniel Nistor
    MIT License, 2023
*/
#include "LEDControllerComposite.h"

void LEDControllerComposite::Initialize()
{
    for (uint8_t i = 0; i < m_leds.Size(); ++i)
    {
        (*m_leds[i])->Initialize();
    }
}

void LEDControllerComposite::Run()
{
    if (!CanRun())
        return;

    for (uint8_t i = 0; i < m_leds.Size(); ++i)
    {
        (*m_leds[i])->Run();
    }
}

void LEDControllerComposite::Configure(uint32_t intervalMs, uint8_t times)
{
    for (uint8_t i = 0; i < m_leds.Size(); ++i)
    {
        (*m_leds[i])->Configure(intervalMs, times);
    }
}

bool LEDControllerComposite::HasFinished() const
{
    bool hasFinished = true;

    for (uint8_t i = 0; i < m_leds.Size(); ++i)
    {
        hasFinished &= (*m_leds[i])->HasFinished();
    }

    return hasFinished;
}

void LEDControllerComposite::Add(ILEDController* led)
{
    m_leds.Add(led);
}

void LEDControllerComposite::Remove(ILEDController* const led)
{
    for (uint8_t i = 0; i < m_leds.Size(); ++i)
    {
        if (m_leds[i] == led)
        {
            m_leds.Remove(i);
        }
    }
}