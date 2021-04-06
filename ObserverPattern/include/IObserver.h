/*
    Author: Daniel Nistor
    Purpose: Subject interface for notifying multiple observers when an event happens. (Observer pattern)
    MIT License, 2021
*/

#pragma once

#include <Arduino.h>

class IObservable;

class IObserver
{
public:
    explicit IObserver(uint16_t events, uint8_t MAX_SUBJECTS_COUNT);
    virtual ~IObserver();

    // Handler
    virtual void OnEvent(uint16_t event) = 0;

    void Add(IObservable& subject);
    void Remove(IObservable& subject);

    void AddEvent(uint16_t event) { m_events |= event; };
    void RemoveEvent(uint16_t event) { m_events ^= event; };

    bool IsOfInterest(uint16_t event) const { return (m_events & event); };

    // non-copyable & non-movable
    IObserver(const IObserver&) = delete;
    IObserver& operator=(const IObserver&) = delete;
    IObserver(IObserver&&) = delete;
    IObserver& operator=(IObserver&&) = delete;

private:
    IObservable** m_subjects = nullptr;
    const uint8_t m_subjectsCount = 0;

    uint16_t m_events = 0;
};