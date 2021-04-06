/*
    Author: Daniel Nistor
    Purpose: Subject interface for notifying multiple observers when an event happens. (Observer pattern)
    MIT License, 2021
*/

#include "IObserver.h"
#include "IObservable.h"

IObserver::IObserver(uint16_t events, uint8_t MAX_SUBJECTS_COUNT)
    : m_subjectsCount(MAX_SUBJECTS_COUNT)
    , m_events(events)
{
    m_subjects = new IObservable*[MAX_SUBJECTS_COUNT];
    
    for (uint8_t i = 0; i < m_subjectsCount; ++i)
        m_subjects[i] = nullptr;
}

IObserver::~IObserver()
{
    for (uint8_t i = 0; i < m_subjectsCount; ++i)
    {
        if (m_subjects[i])
            m_subjects[i]->Unregister(this);
    }

    if (m_subjects)
        delete [] m_subjects;
}

void IObserver::Add(IObservable& subject)
{
    uint8_t freeSlotIndex = m_subjectsCount;
    for (uint8_t i = 0; i < m_subjectsCount; ++i)
    {
        if (m_subjects[i] == &subject)
            return; // already present?

        if (m_subjects[i] == nullptr)
            freeSlotIndex = i; // free slot
    }

    // register anew
    if (freeSlotIndex < m_subjectsCount)
    {
        m_subjects[freeSlotIndex] = &subject;
        m_subjects[freeSlotIndex]->Register(this);
    }
}

void IObserver::Remove(IObservable& subject)
{
    for (uint8_t i = 0; i < m_subjectsCount; ++i)
    {
        if (m_subjects[i] == &subject)
        {
            m_subjects[i]->Unregister(this);
            m_subjects[i] = nullptr; // given that there are no duplicates
            break;
        }
    }
}
