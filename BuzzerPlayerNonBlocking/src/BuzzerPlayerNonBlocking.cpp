/*
 * Copyright (c) 2019, ArduinoGetStarted.com. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * - Neither the name of the ArduinoGetStarted.com nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ARDUINOGETSTARTED.COM "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ARDUINOGETSTARTED.COM BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
// Adaptations made by Daniel Nistor Copyright (c) 2023

#include "BuzzerPlayerNonBlocking.h"

namespace Buzzer
{
    BuzzerPlayerNonBlocking::BuzzerPlayerNonBlocking(uint8_t pwmPin)
        : m_startTime(0), m_playingTime(0), m_noteIndex(0), m_notePauseTime(0), m_pin(pwmPin), m_state(BuzzerState::Idle)
    {
    }

    void BuzzerPlayerNonBlocking::Initialize()
    {
        pinMode(m_pin, OUTPUT);
    }

    void BuzzerPlayerNonBlocking::Stop()
    {
        noTone(m_pin);
        digitalWrite(m_pin, LOW);
        m_state = BuzzerState::Idle;
    }

    void BuzzerPlayerNonBlocking::Play(const Song *song)
    {
        if (!song)
        {
            return;
        }

        m_song = song;
        m_noteIndex = 0;
        m_notePauseTime = 0;
        m_state = BuzzerState::PlayingSong;
        m_startTime = millis();
    }

    void BuzzerPlayerNonBlocking::Play(Note note)
    {
        m_playingTime = (uint32_t)(1000 / (uint8_t)(note.beats));
        m_state = BuzzerState::PlayingNote;
        m_startTime = millis();
    }

    void BuzzerPlayerNonBlocking::Write(uint8_t value) const
    {
        digitalWrite(m_pin, value);
    }

    BuzzerState BuzzerPlayerNonBlocking::State() const
    {
        return m_state;
    }

    void BuzzerPlayerNonBlocking::Run()
    {
        const auto elapsedTime = (uint32_t)(millis() - m_startTime);
        switch (m_state)
        {
        case BuzzerState::Idle:
        {
            break;
        }

        case BuzzerState::PlayingNote:
        {
            if (elapsedTime >= m_playingTime)
            {
                Stop();
            }
            else
            {
                tone(m_pin, (uint32_t)(m_note.frequency));
            }

            break;
        }

        case BuzzerState::PlayingSong:
        {
            if (m_noteIndex < m_song->notesCount)
            {
                if (!m_notePauseTime)
                {
                    // to calculate the note duration, take one second divided by the note type.
                    // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
                    const auto currentNote = m_song->notes[m_noteIndex];
                    const auto duration = 1000 / (uint8_t)(currentNote.beats);
                    tone(m_pin, (uint32_t)(currentNote.frequency), duration);

                    // to distinguish the notes, set a minimum time between them.
                    // the note's duration + 30% seems to work well:
                    m_notePauseTime = duration * (1 + m_song->pause);
                    m_startTime = millis();
                }

                if (elapsedTime >= m_notePauseTime)
                {
                    noTone(m_pin); // stop the tone playing:
                    m_notePauseTime = 0;
                    m_noteIndex++; // play next note
                }
            }
            else
            {
                Stop();
            }

            break;
        }

        default:
            break;
        }
    }
} // namespace Buzzer
