#pragma once

#include "IObserver.h"

namespace
{
    const byte MAX_OBSERVERS_COUNT = 8;
} // anonymous

class ISubject
{
public:
    ISubject();
    ~ISubject() = default;

    void Register(IObserver* observer);
    void Unregister(IObserver* observer);

protected:
    void Notify(byte mask, float newValue);

    IObserver* m_observers[MAX_OBSERVERS_COUNT] = {};
};