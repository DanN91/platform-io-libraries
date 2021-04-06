/*
    Author: Daniel Nistor
    Purpose: Subject interface for notifying multiple observers when an event happens. (Observer pattern)
    MIT License, 2021
*/

#include <Arduino.h>

#include "IObservable.h"
#include "IObserver.h"

IObservable::IObservable(uint8_t MAX_OBSERVERS_COUNT)
    : m_observersCount(MAX_OBSERVERS_COUNT)
{
    m_observers = new IObserver*[MAX_OBSERVERS_COUNT];

    for (uint8_t i = 0; i < m_observersCount; ++i)
        m_observers[i] = nullptr;
}

IObservable::~IObservable()
{
    for (auto i = 0; i < m_observersCount; ++i)
        m_observers[i] = nullptr;

    if (m_observers != nullptr)
        delete [] m_observers;
}

void IObservable::Register(IObserver* observer)
{
    if (observer == nullptr)
        return; // invalid

    // already registered?
    auto freeSlotIndex = m_observersCount;
    for (uint8_t i = 0; i < m_observersCount; ++i)
    {
        if (m_observers[i] == observer)
            return; // don't add it twice

        if (m_observers[i] == nullptr)
            freeSlotIndex = i;
    }

    // register anew
    if (freeSlotIndex < m_observersCount)
        m_observers[freeSlotIndex] = observer;
}

void IObservable::Unregister(IObserver* observer)
{
    if (observer == nullptr)
        return; // invalid

    for (uint8_t i = 0; i < m_observersCount; ++i)
    {
        if (m_observers[i] == observer)
        {
            m_observers[i] = nullptr;
            break; // given that there are no duplicates
        }
    }
}

void IObservable::Notify(uint16_t event)
{
    for (uint8_t i = 0; i < m_observersCount; ++i)
    {
        if (m_observers[i])
            m_observers[i]->OnEvent(event);
    }
}