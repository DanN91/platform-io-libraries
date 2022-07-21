#include <Arduino.h>
#include <TimerManager.h>
#include "CounterWithLEDBlinker.h"
#include "CountdownTimer.h"

bool LED_STATE = false;

TimerManager timerManager(2); // only 1 observer
CounterWithLEDBlinker counterWithBlinker(13, TimerEvent::Second | TimerEvent::Minute | TimerEvent::Hour, timerManager);
class SerialPrinter final : public ITimerDurationPrinter
{
public:
    void print(const TimerDuration& duration) const override
    {
        if (duration.m_days > 0)
        {
            Serial.print(duration.m_days);
            Serial.print(":");
        }

        if (duration.m_hours > 0)
        {
            Serial.print(duration.m_hours);
            Serial.print(":");
        }

        if (duration.m_minutes > 0)
        {
            Serial.print(duration.m_minutes);
            Serial.print(":");
        }

        Serial.println(duration.m_seconds);
    }
};

SerialPrinter durationPrinter;
CountdownTimer countdown({60}, durationPrinter, TimerEvent::Second, timerManager);

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    counterWithBlinker.Register();
    countdown.Register();

    timerManager.Initialize();
    timerManager.Activate();
}

ISR(TIMER1_COMPA_vect)
{
    // Serial.print("Triggered: ");
    // Serial.println(millis());
    timerManager.OnTrigger();
}

void loop()
{
    // put your main code here, to run repeatedly:
}