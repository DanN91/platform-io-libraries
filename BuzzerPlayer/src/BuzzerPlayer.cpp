/*
    File: BuzzerPlayer.cpp
    Author: Arduino.cc
    Website: https://www.arduino.cc/en/Tutorial/PlayMelody

    Adaptations made by Daniel Nistor
*/

#include "BuzzerPlayer.h"

namespace Buzzer
{
    BuzzerPlayer::BuzzerPlayer(byte pwmPin)
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
            delay(((1000 / static_cast<byte>(song.notes[i].beats)) * song.pause) / 100);
        }
    }

    void BuzzerPlayer::Play(Note note) const
    {
        tone(m_buzzerPin, note.frequency);

        // hold the tone according to its value
        delay(1000 / static_cast<byte>(note.beats));

        noTone(m_buzzerPin);
    }
} // namespace Buzzer