#include <Arduino.h>
#include <TogglePushButton.h>

class TestObserver final : public IPushButtonObserver
{
public:
    TestObserver(byte pin)
        : m_pin(pin)
    {}

    void Initialize() const
    {
        pinMode(m_pin, OUTPUT);
    }

    void WasPressed() override
    {
        m_state = !m_state;

        Serial.print("State: ");
        Serial.println(m_state ? "ON" : "OFF");

        digitalWrite(m_pin, m_state);
    }

private:
    const byte m_pin;
    bool m_state = false;
};

TestObserver observer(13);
TogglePushButton button(2, observer);

void setup()
{
    Serial.begin(57600);

    observer.Initialize();
    button.Initialize();
    
    Serial.println("*** PushButton_TEST ***");
}

void loop()
{
  button.HandleEvents();
}