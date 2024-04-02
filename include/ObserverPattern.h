/*
    ...
*/

#pragma once

#include <Vector.h>

template<typename T>
class IObserver;

template<typename T>
class IObservable
{
public:
    explicit IObservable(uint8_t MAX_OBSERVERS_COUNT)
    {
        m_observers.Reserve(MAX_OBSERVERS_COUNT);
    }

    virtual ~IObservable()
    {
        for (uint8_t i = 0; i < m_observers.Size(); ++i)
            Unregister(*m_observers[i]);
    }

    void Register(IObserver<T>* observer)
    {
        if (observer == nullptr)
            return; // invalid

        // already registered?
        for (uint8_t i = 0; i < m_observers.Size(); ++i)
        {
            if (*m_observers[i] == observer)
                return; // don't add it twice
        }

        // register anew
        m_observers.Add(observer);
    }

    void Unregister(IObserver<T>* observer)
    {
        if (observer == nullptr)
            return; // invalid

        for (uint8_t i = 0; i < m_observers.Size(); ++i)
        {
            if (*m_observers[i] == observer)
            {
                m_observers.Remove(i);
                break; // given that there are no duplicates
            }
        }
    }

    // non-copyable & non-movable
    IObservable(const IObservable&) = delete;
    IObservable& operator=(const IObservable&) = delete;
    IObservable(IObservable&&) = delete;
    IObservable& operator=(IObservable&&) = delete;

protected:
    void Notify(T event)
    {
        for (uint8_t i = 0; i < m_observers.Size(); ++i)
        {
            if (const auto observer = m_observers[i]; observer && (*observer)->IsOfInterest(event)) // only relevant notifications
                (*observer)->OnEvent(event);
        }
    }

private:
    Vector<IObserver<T>*> m_observers;
};


template<typename T>
class IObserver
{
public:
    explicit IObserver(T events, IObservable<T>& observable)
        : m_subject(observable)
        , m_events(events)
    {
        // registering is done on demand for more flexibility in event notification order
    }

    virtual ~IObserver()
    {
        m_subject.Unregister(this);
    }

    virtual void Register() { m_subject.Register(this); }
    virtual void Unregister() { m_subject.Unregister(this); }

    // Handler
    virtual void OnEvent(T event) = 0;
    bool IsOfInterest(T event) const { return (int)(m_events & event) != 0; } // at least one event is of interest
    T Events() const { return m_events; }
    void SetEvents(T events) { m_events = events; }

    // non-copyable & non-movable
    IObserver(const IObserver&) = delete;
    IObserver& operator=(const IObserver&) = delete;
    IObserver(IObserver&&) = delete;
    IObserver& operator=(IObserver&&) = delete;

protected:
    IObservable<T>& m_subject;

private:
    T m_events = 0;
};
