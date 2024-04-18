#include <Arduino.h>
#include "Blinker.h"

Blinker::Blinker(IObservable<ButtonState>& subject, uint8_t ledPin)
    : IObserver(ButtonState::Released | ButtonState::Pressed | ButtonState::Held, subject),
      m_pin(ledPin)
{
}

void Blinker::Initialize() const
{
    pinMode(m_pin, OUTPUT);
}

// IObserver
void Blinker::OnEvent(ButtonState event)
{
    if (event == ButtonState::Released)
    {
        Serial.println("Released");

        digitalWrite(m_pin, HIGH);
        delay(1000);
        digitalWrite(m_pin, LOW);
    }
    else if (event == ButtonState::Pressed)
    {
        Serial.println("Pressed");
    }
    else if (event == ButtonState::Held)
    {
        Serial.println("Held");
    }
}
