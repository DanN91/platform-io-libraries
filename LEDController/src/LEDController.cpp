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

LEDController::LEDController(uint8_t digitalPin, uint32_t intervalMs, uint8_t times)
    : m_pin(digitalPin)
    , m_interval(intervalMs)
    , m_times(times)
{
}

void LEDController::Initialize()
{
  pinMode(m_pin, OUTPUT);
  m_state = LOW;
  digitalWrite(m_pin, m_state);
}

void LEDController::Run()
{
  const uint32_t currentMs = millis();
  if (currentMs - m_lastMs >= m_intervalMs)
  {
    m_lastMs = currentMs; // update last time we blinked the LED
    m_state = !m_state;
    digitalWrite(m_pin, m_state); // toggle state
  }
}

void LEDController::Configure(uint32_t intervalMs, uint8_t times)
{
  if (intervalMs != m_intervalMs)
  {
    digitalWrite(m_pin, LOW);
    m_intervalMs = intervalMs;
  }

  if (times != m_times)
  {
    m_times = times;
  }
}
