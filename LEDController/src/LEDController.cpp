/*
    LEDController: Simple interface over one or many LED hardware with non-blocking functionality.
    Author: Daniel Nistor
    MIT License, 2023
*/
#include "LEDController.h"

LEDController::LEDController(uint8_t digitalPin)
    : m_pin(digitalPin)
{
}

void LEDController::Initialize()
{
    pinMode(m_pin, OUTPUT);
    digitalWrite(m_pin, m_state);
}

void LEDController::Run()
{
    if (CanRun() && !HasFinished())
    {
        m_configuration->OnRun(*this);
    }
}

bool LEDController::HasFinished() const
{
    return m_configuration ? m_configuration->HasFinished() : true;
}

void LEDController::Configure(ILEDBlinkConfiguration* configuration)
{
    digitalWrite(m_pin, LOW);
    m_configuration = configuration;
    if (m_configuration)
        m_configuration->Activate();
}

bool LEDController::Toggle()
{
    m_state = !m_state;
    digitalWrite(m_pin, m_state);

    // #FIXME:REMOVE
    Serial.print(m_name ? m_name : "NoName");
    Serial.print(" | Toggle: ");
    Serial.print(!m_state ? "HIGH" : "LOW");
    Serial.print(" -> ");
    Serial.print(m_state ? "HIGH" : "LOW");
    Serial.print(" @ ");
    Serial.println(millis());

    return m_state;
}

LEDController::operator bool() const
{
    return m_configuration ? true : false;
}