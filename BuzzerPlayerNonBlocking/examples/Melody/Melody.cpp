/*
   Created by ArduinoGetStarted.com

   This example code is in the public domain

   Tutorial page: https://arduinogetstarted.com/library/arduino-melody-example
   Library References: https://arduinogetstarted.com/tutorials/arduino-buzzer-library

   This example uses a piezo buzzer:
   + plays a melody once on background each time a button is pressed
   + stops playing a melody when another button is pressed
   + without using delay() function, this is a non-blocking example

   Adapted by Daniel Nistor, 2023
*/

#include <BuzzerPlayerNonBlocking.h>

using namespace Buzzer;

const int BUZZER_PIN = 11;

BuzzerPlayerNonBlocking buzzer(BUZZER_PIN); // create ezBuzzer object that attach to a pin;

constexpr Note TEST_SONG_NOTES[]{
    {NoteFrequency::NOTE_E5, BPS::Eight},
    {NoteFrequency::NOTE_E5, BPS::Eight},
    {NoteFrequency::NOTE_E5, BPS::Four},
    {NoteFrequency::NOTE_E5, BPS::Eight},
    {NoteFrequency::NOTE_E5, BPS::Eight},
    {NoteFrequency::NOTE_E5, BPS::Four},
    {NoteFrequency::NOTE_E5, BPS::Eight},
    {NoteFrequency::NOTE_G5, BPS::Eight},
    {NoteFrequency::NOTE_C5, BPS::Eight},
    {NoteFrequency::NOTE_D5, BPS::Eight},
    {NoteFrequency::NOTE_E5, BPS::Two},
    {NoteFrequency::NOTE_F5, BPS::Eight},
    {NoteFrequency::NOTE_F5, BPS::Eight},
    {NoteFrequency::NOTE_F5, BPS::Eight},
    {NoteFrequency::NOTE_F5, BPS::Eight},
    {NoteFrequency::NOTE_F5, BPS::Eight},
    {NoteFrequency::NOTE_E5, BPS::Eight},
    {NoteFrequency::NOTE_E5, BPS::Eight},
    {NoteFrequency::NOTE_E5, BPS::Sixteen},
    {NoteFrequency::NOTE_E5, BPS::Sixteen},
    {NoteFrequency::NOTE_E5, BPS::Eight},
    {NoteFrequency::NOTE_D5, BPS::Eight},
    {NoteFrequency::NOTE_D5, BPS::Eight},
    {NoteFrequency::NOTE_E5, BPS::Eight},
    {NoteFrequency::NOTE_D5, BPS::Four},
    {NoteFrequency::NOTE_G5, BPS::Four},
};

constexpr Song TestSong{TEST_SONG_NOTES, sizeof(TEST_SONG_NOTES) / sizeof(Note), 80, 0};

void setup()
{
    Serial.begin(115200);

    buzzer.Initialize();

    if (buzzer.State() == BuzzerState::Idle)
    {
        buzzer.Play(&TestSong); // playing
    }

    Serial.println("Initialized.");
}

void loop()
{
    buzzer.Run(); // MUST call the buzzer.Run() function in loop()
}