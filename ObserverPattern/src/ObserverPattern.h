/*
    ...
*/

#pragma once

template<typename T>
class IObserver;

template<typename T>
class IObservable
{
public:
    explicit IObservable(uint8_t MAX_OBSERVERS_COUNT)
        : m_observersCount(MAX_OBSERVERS_COUNT)
    {
        m_observers = new IObserver<T>*[MAX_OBSERVERS_COUNT];

        for (uint8_t i = 0; i < m_observersCount; ++i)
            m_observers[i] = nullptr;
    }

    virtual ~IObservable()
    {
        for (auto i = 0; i < m_observersCount; ++i)
            Unregister(m_observers[i]);

        if (m_observers != nullptr)
            delete [] m_observers;
    }

    void Register(IObserver<T>* observer)
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

    void Unregister(IObserver<T>* observer)
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

    // non-copyable & non-movable
    IObservable(const IObservable&) = delete;
    IObservable& operator=(const IObservable&) = delete;
    IObservable(IObservable&&) = delete;
    IObservable& operator=(IObservable&&) = delete;

protected:
    void Notify(T event)
    {
        for (uint8_t i = 0; i < m_observersCount; ++i)
        {
            if (m_observers[i] && m_observers[i]->IsOfInterest(event)) // only relevant notifications
                m_observers[i]->OnEvent(event);
        }
    }

private:
    IObserver<T>** m_observers = nullptr;
    const uint8_t m_observersCount = 0;
};


template<typename T>
class IObserver
{
public:
    explicit IObserver(T events, IObservable<T>& observable)
        : m_subject(observable)
        , m_events(events)
    {
        m_subject.Register(this);
    }

    virtual ~IObserver()
    {
        m_subject.Unregister(this);
    }

    // Handler
    virtual void OnEvent(T event) = 0;
    bool IsOfInterest(T event) const { return (m_events & event) == event; }
    T Events() const { return m_events; }

    // non-copyable & non-movable
    IObserver(const IObserver&) = delete;
    IObserver& operator=(const IObserver&) = delete;
    IObserver(IObserver&&) = delete;
    IObserver& operator=(IObserver&&) = delete;

private:
    IObservable<T>& m_subject;
    const T m_events = 0;
};
