#include "CountdownTimer.h"

CountdownTimer::CountdownTimer(uint32_t timeInSeconds, const ITimerDurationPrinter& timePrinter, TimerEvent events, IObservable<TimerEvent>& observable)
    : IObserver(events, observable)
    , m_seconds(timeInSeconds)
    , m_printer(timePrinter)
{
}

// IObserver
void CountdownTimer::OnEvent(TimerEvent event)
{
    if ((event & TimerEvent::Second) == TimerEvent::Second)
    {
        // print time
        m_printer.print(TimerDuration(m_seconds));

        // Serial.println("OnSecond");
        if (m_seconds > 0)
            m_seconds--;
        else
            Unregister(); // done counting, unregister
    }
}