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
#include <PushButton.h>

using namespace Buzzer;

constexpr uint8_t BUZZER_PIN = 11;
constexpr uint8_t BUTTON_PIN = 3;

BuzzerPlayerNonBlocking buzzer(BUZZER_PIN); // create ezBuzzer object that attach to a pin;
PushButton button(BUTTON_PIN);

class ButtonHandler final : IObserver<ButtonState>
{
public:
    ButtonHandler(IObservable<ButtonState> &subject, BuzzerPlayerNonBlocking &player)
        : IObserver(ButtonState::Released, subject), m_player(player)
    {
        Register();
    }

    // IObserver
    void OnEvent(ButtonState event) override
    {
        switch (event)
        {
        case ButtonState::Released:
        {
            Serial.println("Released");
            m_player.Stop();
            break;
        }
        }
    }

private:
    BuzzerPlayerNonBlocking &m_player;
};

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

uint32_t lastPlayed = 0;

ButtonHandler handler(button, buzzer);

void setup()
{
    Serial.begin(115200);

    buzzer.Initialize();
    button.Initialize();

    if (buzzer.State() == BuzzerState::Idle)
    {
        buzzer.Play(&TestSong); // playing
        lastPlayed = millis();
    }

    Serial.println("Initialized.");
}

void loop()
{
    buzzer.Run(); // MUST call the buzzer.Run() function in loop()
    button.HandleEvents();

    if (millis() - lastPlayed > 10000 && buzzer.State() == BuzzerState::Idle)
    {
        buzzer.Play(&TestSong); // playing
        lastPlayed = millis();
    }
}