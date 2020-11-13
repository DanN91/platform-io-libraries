#include "ISubject.h"

ISubject::ISubject()
{
    for (byte i = 0; i < MAX_OBSERVERS_COUNT; ++i)
        m_observers[i] = nullptr;
}

void ISubject::Register(IObserver* observer)
{
    if (observer == nullptr)
        return;

    // already registered?
    byte freeSlotIndex = MAX_OBSERVERS_COUNT;
    for (byte i = 0; i < MAX_OBSERVERS_COUNT; ++i)
    {
        if (m_observers[i] == observer)
            return;

        if (m_observers[i] == nullptr)
            freeSlotIndex = i;
    }

    // register anew
    if (freeSlotIndex < MAX_OBSERVERS_COUNT)
        m_observers[freeSlotIndex] = observer;
}

void ISubject::Unregister(IObserver* observer)
{
    for (byte i = 0; i < MAX_OBSERVERS_COUNT; ++i)
    {
        if (m_observers[i] == observer)
        {
            m_observers[i] = nullptr;
            break;
        }
    }
}

void ISubject::Notify(byte mask, float value)
{
    for (byte i = 0; i < MAX_OBSERVERS_COUNT; ++i)
    {
        if (m_observers[i] && m_observers[i]->IsOfInterest(mask))
            m_observers[i]->Update(mask, value);
    }
}