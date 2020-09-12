/*
    File: BuzzerPlayer.h
    Author: Arduino.cc
    Website: https://www.arduino.cc/en/Tutorial/PlayMelody

    Adaptations made by Daniel Nistor
*/

#pragma once

#include <Arduino.h>

#include "../include/Sound.h"
#include "../include/Songs.h"

namespace Buzzer
{
    class BuzzerPlayer final
    {
    public:
        explicit BuzzerPlayer(uint8_t pwmPin);
        void Initialize() const;

        void Play(Song song) const;
        void Play(Note note) const;

    private:
        uint8_t m_buzzerPin;
    };
} // namespace Buzzer
