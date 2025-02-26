#include <Arduino.h>

#include "ObserverPattern.h"

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
        Serial.print("Event received: ");
        Serial.println(event);
    }
};

// Explicit instantiation of template classes
template class IObservable<MyEvent::EventType>;
template class IObserver<MyEvent::EventType>;

MyObservable observable;
MyObserver observer1(MyEvent::EVENT_TYPE_1, observable);
MyObserver observer2(MyEvent::EVENT_TYPE_2, observable);

void setup()
{
    Serial.begin(115200);
    delay(1000); // Wait for Serial to initialize

    Serial.println("Triggering EVENT_TYPE_1");
    observable.TriggerEvent(MyEvent::EVENT_TYPE_1);

    Serial.println("Triggering EVENT_TYPE_2");
    observable.TriggerEvent(MyEvent::EVENT_TYPE_2);
}

void loop()
{
    // Nothing to do here
}