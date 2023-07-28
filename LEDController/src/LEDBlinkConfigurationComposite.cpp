/*
    LEDBlinkConfigurationComposite: Configuration for non-blocking blinking of multiple LEDs.
    Author: Daniel Nistor
    MIT License, 2023
*/
#include "LEDBlinkConfigurationComposite.h"

void LEDBlinkConfigurationComposite::Activate()
{
    for (uint8_t i = 0; i < m_configurations.Size(); ++i)
    {
        (*m_configurations[i])->Activate();
    }
}

void LEDBlinkConfigurationComposite::OnRun(ILEDToggler& toggler)
{
    if (m_currentIndex >= m_configurations.Size())
        return;

    auto configuration = GetCurrentConfiguration();
    if (configuration->HasFinished())
    {
        m_currentIndex++;
        configuration = GetCurrentConfiguration();
        configuration->Activate();
    }

    configuration->OnRun(toggler);
}

bool LEDBlinkConfigurationComposite::HasFinished() const
{
    bool hasFinished = true;

    for (uint8_t i = 0; i < m_configurations.Size() && hasFinished; ++i)
    {
        hasFinished &= (*m_configurations[i])->HasFinished();
    }

    return hasFinished;
}

void LEDBlinkConfigurationComposite::Reset()
{
    for (uint8_t i = 0; i < m_configurations.Size(); ++i)
    {
        (*m_configurations[i])->Reset();
    }
}

void LEDBlinkConfigurationComposite::Add(ILEDBlinkConfiguration* configuration)
{
    m_configurations.Add(configuration);
}

void LEDBlinkConfigurationComposite::Remove(ILEDBlinkConfiguration* configuration)
{
    for (uint8_t i = 0; i < m_configurations.Size(); ++i)
    {
        if (m_configurations[i] == configuration)
        {
            m_configurations.Remove(i);
        }
    }
}

ILEDBlinkConfiguration* LEDBlinkConfigurationComposite::GetCurrentConfiguration() const
{
    return (m_currentIndex >= m_configurations.Size()) ? nullptr : (*m_configurations[m_currentIndex]);
}