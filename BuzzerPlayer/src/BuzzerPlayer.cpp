/*
    File: BuzzerPlayer.cpp
    Author: Arduino.cc
    Website: https://www.arduino.cc/en/Tutorial/PlayMelody

    Adaptations made by Daniel Nistor
*/

#include "BuzzerPlayer.h"

namespace Buzzer
{
    BuzzerPlayer::BuzzerPlayer(uint8_t pwmPin)
        : m_buzzerPin(pwmPin)
    {
        // nothing more
    }

    void BuzzerPlayer::Initialize() const
    {
        pinMode(m_buzzerPin, OUTPUT);
    }

    void BuzzerPlayer::Play(Song song) const
    {
        // play all notes in the song
        for (byte i = 0; i < song.notesCount; ++i)
        {
            // play note
            Play(song.notes[i]);
            // and pause between each note? value is % percent of the note's duration
            delay(((1000 / static_cast<uint8_t>(song.notes[i].beats)) * song.pause) / 100);
        }
    }

    void BuzzerPlayer::Play(Note note) const
    {
        tone(m_buzzerPin, static_cast<uint32_t>(note.frequency));
        delay(1000 / static_cast<uint16_t>(note.beats));

        noTone(m_buzzerPin);
    }

    void BuzzerPlayer::Play(uint32_t frequency) const
    {
        tone(m_buzzerPin, frequency);
    }

    void BuzzerPlayer::Play(uint32_t frequency, uint32_t duration) const
    {
        tone(m_buzzerPin, frequency, duration);
    }

    void BuzzerPlayer::Stop() const
    {
        noTone(m_buzzerPin);
    }


} // namespace Buzzer