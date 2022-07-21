#include "CounterWithLEDBlinker.h"

CounterWithLEDBlinker::CounterWithLEDBlinker(uint8_t LED_PIN, TimerEvent events, IObservable<TimerEvent> &observable)
    : IObserver(events, observable),
      m_ledPin(LED_PIN)
{
}

// IObserver
void CounterWithLEDBlinker::OnEvent(TimerEvent event)
{
    if ((event & TimerEvent::Second) == TimerEvent::Second)
    {
        printTime();

        // Serial.println("OnSecond");
        m_ledState = !m_ledState;
        digitalWrite(m_ledPin, m_ledState);
        m_seconds++;
    }

    if ((event & TimerEvent::Minute) == TimerEvent::Minute)
    {
        // Serial.println("OnMinute");
        m_minutes++;
    }

    if ((event & TimerEvent::Hour) == TimerEvent::Hour)
    {
        // Serial.println("OnHour");
        m_hours++;
    }

    // fit to proper units
    m_hours %= 24;
    m_minutes %= 60;
    m_seconds %= 60;
}

void CounterWithLEDBlinker::printTime() const
{
    Serial.print("Time: ");
    if (m_hours < 10)
        Serial.print("0");
    Serial.print(m_hours);
    Serial.print(":");
    if (m_minutes < 10)
        Serial.print("0");
    Serial.print(m_minutes);
    Serial.print(":");
    if (m_seconds < 10)
        Serial.print("0");
    Serial.println(m_seconds);
}