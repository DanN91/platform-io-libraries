/*
    TimerManager: Facade wrapping ATMEGA328 TIMER_1 functionality using ObserverPattern
    Author: Daniel Nistor
    MIT License, 2022
    Adaptated from https://www.youtube.com/watch?v=IdL0_ZJ7V2s
*/
#pragma once

#include <ObserverPattern.h>
#include "TimerManagerMasks.h"

/*
    fClock = 16 000 000 Hz = 16 MHz ~= 1 second
    Start value formula: TCNT1 = 65536 - (fClock/prescaler * fTarget)
    Compare value formula: OCR1A = (fClock/(prescaler * fTarget)) - 1
        1 second: (16*10^6 / 256)    - 1 => 62500 => Prescaler: TCCR1B |= (1 << CS12)
        1 second: (16*10^6 / 1024)   - 1 => 15624 => Prescaler: TCCR1B |= (1 << CS12) | (1 << CS10)
*/

class TimerManager final : public IObservable<TimerEvent>
{
public:
    TimerManager(uint8_t MAX_OBSERVERS_COUNT);
    virtual ~TimerManager() = default;

    void Initialize() const;
    void Activate() const;
    void Deactivate() const;

    // non-movable && non-copyable
    TimerManager(TimerManager&&) = delete;
    TimerManager& operator=(TimerManager&&) = delete;
    TimerManager(const TimerManager&) = delete;
    TimerManager& operator=(const TimerManager&) = delete;

    void OnTrigger(); // This should be called only by the Timer ISR

private:
    void OnSecondElapsed();
    void OnMinuteElapsed();
    void OnHourElapsed();
    void OnDayElapsed();
    void OnWeekElapsed();
    void OnMonthElapsed();

    uint8_t m_seconds = 0; // max 65535 => overflows in ~18h
    uint8_t m_minutes = 0;
    uint8_t m_hours = 0;
    uint8_t m_days = 0;
    uint8_t m_weeks = 0;
};