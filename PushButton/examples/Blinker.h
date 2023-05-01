#include <Arduino.h>

#include <ObserverPattern.h>
#include <PushButton.h>

class Blinker final : public IObserver<ButtonState>
{
public:
    explicit Blinker(IObservable<ButtonState>& subject, uint8_t ledPin);
    ~Blinker() = default;

    void Initialize() const;

    // IObserver
    void OnEvent(ButtonState event) override;

    // non-copyable & non-movable
    Blinker(const Blinker &) = delete;
    Blinker &operator=(const Blinker &) = delete;
    Blinker(Blinker &&) = delete;
    Blinker &operator=(Blinker &&) = delete;

private:
    uint8_t m_pin;
};