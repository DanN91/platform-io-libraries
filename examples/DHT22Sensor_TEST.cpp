#include <Arduino.h>

#include <DHT22Sensor.h>

class BlinkObserver final : public IObserver<DHT22Mask>
{
public:
    BlinkObserver(DHT22Sensor &subject, uint8_t lowerPin, uint8_t inRangePin, uint8_t greaterPin)
        : IObserver(DHT22Mask::Humidity | DHT22Mask::Temperature, subject),
        m_lowerPin(lowerPin), m_inRangePin(inRangePin), m_higherPin(greaterPin)
    {
    }

    void Initialize() const
    {
        pinMode(m_lowerPin, OUTPUT);
        pinMode(m_inRangePin, OUTPUT);
        pinMode(m_higherPin, OUTPUT);
    }

    // IObserver
    void OnEvent(DHT22Mask mask) override
    {

    }

private:
    static void BlinkLED(byte ledPin)
    {
        digitalWrite(ledPin, HIGH);
        delay(1000);
        digitalWrite(ledPin, LOW);
        delay(1000);
    }

    static void BlinkERROR(byte lower, byte inRange, byte higher)
    {
        digitalWrite(lower, HIGH);
        digitalWrite(inRange, HIGH);
        digitalWrite(higher, HIGH);

        delay(2000);

        digitalWrite(lower, LOW);
        digitalWrite(inRange, LOW);
        digitalWrite(higher, LOW);

        delay(2000);
    }

    const uint8_t m_lowerPin;
    const uint8_t m_inRangePin;
    const uint8_t m_higherPin;
};

constexpr const uint8_t LOWER_LED_PIN = 0;
constexpr const uint8_t IN_RANGE_LED_PIN = 1;
constexpr const uint8_t HIGHER_LED_PIN = 2;

constexpr const uint8_t DHT22_PIN = 3;

DHT22Sensor dhtSensor(DHT22_PIN, 50, 10);
BlinkObserver blinker(dhtSensor, LOWER_LED_PIN, IN_RANGE_LED_PIN, HIGHER_LED_PIN);

void setup()
{
    dhtSensor.Initialize();
    blinker.Initialize();
}

void loop()
{
    dhtSensor.HandleEvents();
    delay(2000);
}