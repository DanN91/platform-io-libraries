/*
    TimerManager: Facade wrapping ATMEGA328 TIMER_1 functionality using ObserverPattern
    Author: Daniel Nistor
    MIT License, 2022
    Adaptated from https://www.youtube.com/watch?v=IdL0_ZJ7V2s
*/

#include <Arduino.h>

#include "TimerManager.h"

TimerManager::TimerManager(uint8_t MAX_OBSERVERS_COUNT)
    : IObservable<TimerEvent>(MAX_OBSERVERS_COUNT)
{
}

void TimerManager::Initialize() const
{
    TCCR1A = 0; // initialize timer
    TCCR1B = 0;
    OCR1A = 15624; // this will be matched once every second

    TCCR1B &= ~(1 << WGM13); // make sure PWM mode is cleared
    TCCR1B |= (1 << CS12) | (1 << CS10) | (1 << WGM12); // Prescaller: 1024, Clear Timer on Compare Mode
}

void TimerManager::Activate() const
{
    TIMSK1 |= (1 << OCIE1A); // enable interrupt on OCR1A match
    sei(); // enable global interrupts
}

void TimerManager::Deactivate() const
{
    cli(); // disable global interrupts
    TIMSK1 &= ~(1 << OCIE1A); // disable interrupt on OCR1A match
}

void TimerManager::OnTrigger()
{
    OnSecondElapsed();
}

void TimerManager::OnSecondElapsed()
{
    m_seconds++;
    m_seconds %= 60;
    // minute passed
    (m_seconds == 0) ? OnMinuteElapsed() : Notify(TimerEvent::Second);
}

void TimerManager::OnMinuteElapsed()
{
    m_minutes++;
    m_minutes %= 60;
    // hour passed
    (m_minutes == 0) ? OnHourElapsed() : Notify(TimerEvent::Second | TimerEvent::Minute);
}

void TimerManager::OnHourElapsed()
{
    m_hours++;
    m_hours %= 24;
    // day passed
    (m_hours == 0) ? OnDayElapsed() : Notify(TimerEvent::Second | TimerEvent::Minute | TimerEvent::Hour);
}

void TimerManager::OnDayElapsed()
{
    m_days++;
    m_days %= 7;
    // week passed
    (m_days == 0) ? OnWeekElapsed() : Notify(TimerEvent::Second | TimerEvent::Minute | TimerEvent::Hour | TimerEvent::Day);
}

void TimerManager::OnWeekElapsed()
{
    m_weeks++;
    m_weeks %= 4;
    // month passed
    (m_weeks == 0) ? OnMonthElapsed() : Notify(TimerEvent::Second | TimerEvent::Minute | TimerEvent::Hour | TimerEvent::Day | TimerEvent::Week);
}

void TimerManager::OnMonthElapsed()
{
    Notify(TimerEvent::Second | TimerEvent::Minute | TimerEvent::Hour | TimerEvent::Day | TimerEvent::Week | TimerEvent::Month);
}
