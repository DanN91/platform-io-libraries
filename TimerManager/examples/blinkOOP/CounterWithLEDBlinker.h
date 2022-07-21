#include <Arduino.h>
#include <ObserverPattern.h>
#include <TimerManagerMasks.h>

class CounterWithLEDBlinker final : public IObserver<TimerEvent>
{
public:
    CounterWithLEDBlinker(uint8_t LED_PIN, TimerEvent events, IObservable<TimerEvent>& observable);
    virtual ~CounterWithLEDBlinker() = default;

    // IObserver
    void OnEvent(TimerEvent event) override;

private:
    void printTime() const;

    const uint8_t m_ledPin;
    bool m_ledState = 0;

    // clock
    uint8_t m_hours = 0;
    uint8_t m_minutes = 0;
    uint8_t m_seconds = 0;
};