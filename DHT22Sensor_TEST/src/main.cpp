#include <Arduino.h>

#include <BlinkObserver.h>
#include <DHT22Sensor.h>

constexpr const byte LOWER_LED_PIN = 0;
constexpr const byte IN_RANGE_LED_PIN = 1;
constexpr const byte HIGHER_LED_PIN = 2;
constexpr const byte DHT22_PIN = 3;

DHT22Sensor dhtSensor(DHT22_PIN, DHT22Mask::Humidity, 10, 10);
BlinkObserver blinker(dhtSensor, LOWER_LED_PIN, IN_RANGE_LED_PIN, HIGHER_LED_PIN);

void setup()
{
    dhtSensor.Initialize();
    blinker.Initialize();
}

void loop()
{
    dhtSensor.ReadValues();
    delay(2000);
}