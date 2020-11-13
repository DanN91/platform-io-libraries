#pragma once

#include <Arduino.h>

class ISubject;

namespace
{
    const byte MAX_SUBJECTS_COUNT = 3;
} // anonymous

class IObserver
{
public:
    IObserver(ISubject& subject, uint16_t mask);
    virtual ~IObserver();

    virtual void Update(uint16_t mask, float newValue) = 0;

    void Add(ISubject& subject);
    void Remove(ISubject& subject);

    void AddMask(uint16_t mask)
    {
        m_mask |= mask;
    };

    void RemoveMask(uint16_t mask)
    {
        m_mask ^= mask;
    };

    bool IsOfInterest(uint16_t mask) const
    {
        return (m_mask & mask);
    };

    IObserver(const IObserver&) = delete;
    IObserver& operator=(const IObserver&) = delete;
    IObserver(IObserver&&) = delete;
    IObserver& operator=(IObserver&&) = delete;

private:
    ISubject* m_subjects[MAX_SUBJECTS_COUNT];
    uint16_t  m_mask;
};