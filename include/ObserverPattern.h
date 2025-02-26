/*
    Observer Pattern Implementation
    Author: Daniel Nistor
    License: MIT

    This file provides an implementation of the Observer pattern using templates.
    The Observer pattern is a behavioral design pattern in which an object, called the subject, maintains a list of its dependents, called observers, and notifies them automatically of any state changes, usually by calling one of their methods.

    The `IObservable` class represents the subject that can be observed by multiple observers. It maintains a list of observers and provides methods to register and unregister observers. It also provides a method to notify all registered observers of an event.

    The `IObserver` class represents an observer that can register itself with an observable subject to receive notifications of events.
    It provides methods to register and unregister itself with the subject, and a method to handle events.

    Usage:
    - Extend the `IObservable` class to create a concrete observable subject.
    - Extend the `IObserver` class to create a concrete observer that can handle specific events.
    - Use the `Register` and `Unregister` methods to manage the list of observers.
    - Use the `Notify` method to notify all registered observers of an event.

    Example:
    class MyEvent
    {
    public:
        enum EventType { EVENT_TYPE_1 = 1, EVENT_TYPE_2 = 2 };
    };

    class MyObservable : public IObservable<MyEvent::EventType>
    {
    public:
        MyObservable() : IObservable(10) {} // Maximum 10 observers

        void TriggerEvent(MyEvent::EventType event)
        {
            Notify(event);
        }
    };

    class MyObserver : public IObserver<MyEvent::EventType>
    {
    public:
        MyObserver(MyEvent::EventType events, MyObservable& observable)
            : IObserver(events, observable)
        {
            Register();
        }

        void OnEvent(MyEvent::EventType event) override
        {
            // Handle the event
        }
    };
*/

#pragma once

#include <Vector.h>

template<typename T>
class IObserver;

template<typename T>
class IObservable
{
public:
    explicit IObservable(uint8_t MAX_OBSERVERS_COUNT);
    virtual ~IObservable();

    void Register(IObserver<T>* observer);
    void Unregister(IObserver<T>* observer);

    // non-copyable & non-movable
    IObservable(const IObservable&) = delete;
    IObservable& operator=(const IObservable&) = delete;
    IObservable(IObservable&&) = delete;
    IObservable& operator=(IObservable&&) = delete;

protected:
    void Notify(T event);

private:
    Vector<IObserver<T>*> m_observers;
};

template<typename T>
IObservable<T>::IObservable(uint8_t MAX_OBSERVERS_COUNT)
{
    m_observers.Reserve(MAX_OBSERVERS_COUNT);
}

template<typename T>
IObservable<T>::~IObservable()
{
    for (uint8_t i = 0; i < m_observers.Size(); ++i)
        Unregister(*m_observers[i]);
}

template<typename T>
void IObservable<T>::Register(IObserver<T>* observer)
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

template<typename T>
void IObservable<T>::Unregister(IObserver<T>* observer)
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

template<typename T>
void IObservable<T>::Notify(T event)
{
    for (uint8_t i = 0; i < m_observers.Size(); ++i)
    {
        const auto observer = m_observers[i];
        if (observer && (*observer)->IsOfInterest(event)) // only relevant notifications
            (*observer)->OnEvent(event);
    }
}

template<typename T>
class IObserver
{
public:
    explicit IObserver(T events, IObservable<T>& observable);
    virtual ~IObserver();

    virtual void Register();
    virtual void Unregister();

    // Handler
    virtual void OnEvent(T event) = 0;
    bool IsOfInterest(T event) const;
    T Events() const;
    void SetEvents(T events);

    // non-copyable & non-movable
    IObserver(const IObserver&) = delete;
    IObserver& operator=(const IObserver&) = delete;
    IObserver(IObserver&&) = delete;
    IObserver& operator=(IObserver&&) = delete;

protected:
    IObservable<T>& m_subject;

private:
    T m_events;
};

template<typename T>
IObserver<T>::IObserver(T events, IObservable<T>& observable)
    : m_subject(observable)
    , m_events(events)
{
    // registering is done on demand for more flexibility in event notification order
}

template<typename T>
IObserver<T>::~IObserver()
{
    m_subject.Unregister(this);
}

template<typename T>
void IObserver<T>::Register()
{
    m_subject.Register(this);
}

template<typename T>
void IObserver<T>::Unregister()
{
    m_subject.Unregister(this);
}

template<typename T>
bool IObserver<T>::IsOfInterest(T event) const
{
    return (int)(m_events & event) != 0; // at least one event is of interest
}

template<typename T>
T IObserver<T>::Events() const
{
    return m_events;
}

template<typename T>
void IObserver<T>::SetEvents(T events)
{
    m_events = events;
}