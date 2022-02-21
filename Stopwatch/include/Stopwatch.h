/*
    Stopwatch: track time in milliseconds or seconds by using a pushbutton for starting and stopping the watch.
    Author: Daniel Nistor
    License: MIT
*/

#pragma once

#include <Arduino.h>

#include <ObserverPattern.h>
#include <PushButtonMasks.h>
#include <IStopwatchHandler.h>

class Stopwatch final : public IObserver<ButtonState>
{
public:
    Stopwatch(IObservable<ButtonState>& button);
    Stopwatch(IObservable<ButtonState>& button, IStopwatchHandler* handler);
    ~Stopwatch() = default;

    // IObserver
    void OnEvent(ButtonState event) override;

    uint32_t DurationMs() const;
    uint32_t DurationSec() const;

private:
    void Start();
    void Stop();
    bool IsRunning() const;

    uint32_t m_stoppedAtMs = 0;
    uint32_t m_startedAtMs = 0;
    // Handler
    IStopwatchHandler* const m_handler = nullptr;
};