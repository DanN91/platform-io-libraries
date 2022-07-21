#pragma once

#include <Arduino.h>

#include <ObserverPattern.h>
#include <TimerManagerMasks.h>
#include "ITimerDurationPrinter.h"

class CountdownTimer final : public IObserver<TimerEvent>
{
public:
    CountdownTimer(uint32_t timeInSeconds, const ITimerDurationPrinter& timePrinter, TimerEvent events, IObservable<TimerEvent>& observable);
    virtual ~CountdownTimer() = default;

    // IObserver
    void OnEvent(TimerEvent event) override;

private:
    uint32_t m_seconds;
    const ITimerDurationPrinter& m_printer;
};