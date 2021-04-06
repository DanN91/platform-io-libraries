/*
    Author: Daniel Nistor
    Purpose: Subject interface for notifying multiple observers when an event happens. (Observer pattern)
    MIT License, 2021
*/

#pragma once

#include <Arduino.h>

class IObserver;

class IObservable
{
public:
    explicit IObservable(uint8_t MAX_OBSERVERS_COUNT);
    virtual ~IObservable();

    void Register(IObserver* observer);
    void Unregister(IObserver* observer);

    // non-copyable & non-movable
    IObservable(const IObservable&) = delete;
    IObservable& operator=(const IObservable&) = delete;
    IObservable(IObservable&&) = delete;
    IObservable& operator=(IObservable&&) = delete;

protected:
    void Notify(uint16_t event);

    IObserver** m_observers = nullptr;
    const uint8_t m_observersCount = 0;
};