/*
    LEDController: Simple interface over one or many LED hardware with non-blocking functionality.
    Author: Daniel Nistor
    MIT License, 2023
*/
#pragma once

#include <Arduino.h>

#include "ILEDController.h"

class LEDController final : public ILEDController
{
public:
  LEDController(uint8_t digitalPin);
  LEDController(uint8_t digitalPin, uint32_t intervalMs);
  LEDController(uint8_t digitalPin, uint32_t intervalMs, uint8_t times);
  ~LEDController() = default;

  virtual void Initialize();

  virtual void Run();
  virtual bool HasFinished() const;

  virtual void Configure(uint32_t intervalMs, uint8_t times);

  // non-copyable & non-movable
  LEDController(const LEDController &) = delete;
  LEDController &operator=(const LEDController &) = delete;
  LEDController(LEDController &&) = delete;
  LEDController &operator=(LEDController &&) = delete;

private:
  void Toggle();

  const uint8_t m_pin;
  bool m_state = LOW;
};
