/*
    LEDPattern: Simple interface for blinking an LED in a specific pattern.
    Author: Daniel Nistor
    MIT License, 2023
*/
#pragma once

#include <Arduino.h>

class LEDPattern final
{
public:
  LEDPattern();
  ~LEDPattern() = default;

  void Configure();
  void Play();

  // non-copyable & non-movable
  LEDPattern(const LEDPattern &) = delete;
  LEDPattern &operator=(const LEDPattern &) = delete;
  LEDPattern(LEDPattern &&) = delete;
  LEDPattern &operator=(LEDPattern &&) = delete;

private:
  
};
