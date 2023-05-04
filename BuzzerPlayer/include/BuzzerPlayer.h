/*
    File: BuzzerPlayer.h
    Author: Arduino.cc
    Website: https://www.arduino.cc/en/Tutorial/PlayMelody

    Adaptations made by Daniel Nistor
*/

#pragma once

#include <Arduino.h>

#include "Sound.h"
#include "Songs.h"

namespace Buzzer
{
  class BuzzerPlayer final
  {
  public:
    explicit BuzzerPlayer(uint8_t pwmPin);
    void Initialize() const;

    void Play(Song song) const;
    void Play(Note note) const;
    void Play(uint32_t frequency) const;
    void Play(uint32_t frequency, uint32_t durationMs) const;
    void Write(uint8_t value) const;
    void Stop() const;

  private:
    uint8_t m_pin;
  };
} // namespace Buzzer
