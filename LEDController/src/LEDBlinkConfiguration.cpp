/*
    LEDBlinkConfiguration: Configuration for non-blocking blinking of an LED.
    Author: Daniel Nistor
    MIT License, 2023
*/
#include "LEDBlinkConfiguration.h"

LEDBlinkConfiguration::LEDBlinkConfiguration(uint32_t intervalMs)
    : ILEDBlinkConfiguration(intervalMs)
{
}

LEDBlinkConfiguration::LEDBlinkConfiguration(uint32_t intervalMs, uint8_t times)
    : ILEDBlinkConfiguration(intervalMs, times)
{
}

void LEDBlinkConfiguration::Activate()
{
    m_lastMs = millis();
}

void LEDBlinkConfiguration::OnRun(ILEDToggler& toggler)
{
    const uint32_t currentMs = millis();
    if (!HasFinished() && (currentMs - m_lastMs) >= m_intervalMs)
    {
        // #FIXME:REMOVE
        Serial.print("OnRun @ ");
        Serial.print(currentMs);
        // Serial.print(" | Interval: ");
        // Serial.println(m_intervalMs);
        const auto state = toggler.Toggle();
        m_lastMs = millis();

        if (!state) // count only when the LED turns OFF
        {
            m_countTimes++;
            Serial.print(" | Count: ");
            Serial.println(m_countTimes);
        }
    }
}

bool LEDBlinkConfiguration::HasFinished() const
{
    return m_countTimes >= m_times;
}

void LEDBlinkConfiguration::Reset()
{
    m_countTimes = 0;
}
