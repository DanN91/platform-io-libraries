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

LEDController::LEDController(uint8_t digitalPin, uint32_t intervalMs)
    : ILEDController(intervalMs)
    , m_pin(digitalPin)
{
}

LEDController::LEDController(uint8_t digitalPin, uint32_t intervalMs, uint8_t times)
    : ILEDController(intervalMs, times)
    , m_pin(digitalPin)
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

  if (CanRun() && !HasFinished() && (currentMs - m_lastMs) >= m_intervalMs)
  {
    Toggle();

    if (!m_state) // count only when the LED turns OFF
    {
      m_countTimes += 1;

      Serial.print("Counting: ");
      Serial.println(m_countTimes);
    }
  }
}

void LEDController::Configure(uint32_t intervalMs, uint8_t times)
{
  digitalWrite(m_pin, LOW);
  m_intervalMs = intervalMs;

  m_times = times;
  m_countTimes = 0;
}

inline bool LEDController::HasFinished() const
{
  return (m_countTimes >= m_times);
}

void LEDController::Toggle()
{
  m_state = !m_state;
  m_lastMs = millis(); // update last time we blinked the LED
  digitalWrite(m_pin, m_state); // toggle state
}
