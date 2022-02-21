/*
    Stopwatch: track time in milliseconds or seconds by using a pushbutton for starting and stopping the watch.
    Author: Daniel Nistor
    License: MIT
*/

#include "Stopwatch.h"

#include <PushButton.h>

Stopwatch::Stopwatch(IObservable<ButtonState>& button)
    : IObserver<ButtonState>(ButtonState::Released, button)
{
}

Stopwatch::Stopwatch(IObservable<ButtonState>& button, IStopwatchHandler* handler)
    : IObserver<ButtonState>(ButtonState::Pressed | ButtonState::Released, button)
    , m_handler(handler)
{
}

void Stopwatch::OnEvent(ButtonState event)
{
    // #TODO:Think of a better way to split the functionality
    if (m_handler)
    {
        switch (event)
        {
            case ButtonState::Pressed:
                Start();
                break;
            case ButtonState::Released:
                Stop();
                break;
        }
    }
    else
    {
        if (event == ButtonState::Released)
            IsRunning() ? Stop() : Start();
    }
}

void Stopwatch::Start()
{
    m_startedAtMs = millis();
    if (m_handler)
        m_handler->OnStart();
}

void Stopwatch::Stop()
{
    m_stoppedAtMs = millis();
    if (m_handler)
        m_handler->OnStop();
}

bool Stopwatch::IsRunning() const
{
    return m_startedAtMs > m_stoppedAtMs;
}

uint32_t Stopwatch::DurationMs() const
{
    return (m_stoppedAtMs < m_startedAtMs) ? 0 : (m_stoppedAtMs - m_startedAtMs);
}

uint32_t Stopwatch::DurationSec() const
{
    return DurationMs() / 1000;
}