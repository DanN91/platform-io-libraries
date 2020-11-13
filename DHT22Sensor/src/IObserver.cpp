#include "IObserver.h"
#include "ISubject.h"

IObserver::IObserver(ISubject& subject, uint16_t mask)
    : m_mask(mask)
{
    m_subjects[0] = &subject;

    for (byte i = 1; i < MAX_SUBJECTS_COUNT; ++i)
        m_subjects[i] = nullptr;

    m_subjects[0]->Register(this);
}

IObserver::~IObserver()
{
    for (byte i = 0; i < MAX_SUBJECTS_COUNT; ++i)
    {
        if (m_subjects[i])
            m_subjects[i]->Unregister(this);
    }
}

void IObserver::Add(ISubject& subject)
{
    // already present?
    byte freeSlotIndex = MAX_SUBJECTS_COUNT;
    for (byte i = 0; i < MAX_SUBJECTS_COUNT; ++i)
    {
        if (m_subjects[i] == &subject)
            return;

        if (m_subjects[i] == nullptr)
            freeSlotIndex = i;
    }

    // register anew
    if (freeSlotIndex < MAX_SUBJECTS_COUNT)
    {
        m_subjects[freeSlotIndex] = &subject;
        m_subjects[freeSlotIndex]->Register(this);
    }
}

void IObserver::Remove(ISubject& subject)
{
    for (byte i = 0; i < MAX_SUBJECTS_COUNT; ++i)
    {
        if (m_subjects[i] == &subject)
        {
            m_subjects[i]->Unregister(this);
            m_subjects[i] = nullptr;
            break;
        }
    }
}