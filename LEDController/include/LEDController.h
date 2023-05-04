/*
    LEDController: Simple interface over one or many LED hardware with non-blocking functionality.
    Author: Daniel Nistor
    MIT License, 2023
*/
#pragma once

#include <Arduino.h>

class LEDController final
{
public:
  LEDController(uint8_t digitalPin);
  LEDController(uint8_t digitalPin, uint32_t intervalMs);
  LEDController(uint8_t digitalPin, uint32_t intervalMs, uint8_t times);
  ~LEDController() = default;

  void Initialize();
  void Run();

  void Configure(uint32_t intervalMs, uint8_t times);

  // non-copyable & non-movable
  LEDController(const LEDController &) = delete;
  LEDController &operator=(const LEDController &) = delete;
  LEDController(LEDController &&) = delete;
  LEDController &operator=(LEDController &&) = delete;

private:
  const uint8_t m_pin;
  uint8_t m_state = LOW;
  uint32_t m_intervalMs = 0;
  uint8_t m_times = 1;
  uint32_t m_lastMs = 0;
};
