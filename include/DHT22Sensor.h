#pragma once

#include <Arduino.h>
#include <ObserverPattern.h>

#include "DHT22.h"
#include "DHT22SensorMasks.h"

class DHT22Sensor final : public IObservable<DHT22Mask>
{
public:
    DHT22Sensor(uint8_t pin, uint8_t MAX_OBSERVERS_COUNT = 1);
    DHT22Sensor(uint8_t pin, uint8_t temperatureTrigger, uint8_t humidityTrigger, uint8_t MAX_OBSERVERS_COUNT = 1);

    void Initialize();

    void HandleEvents();

    float Temperature() const;
    float Humidity() const;

    // Device specifications
    static const int8_t DHT22_MIN_TEMPERATURE = -40;
    static const int8_t DHT22_MAX_TEMPERATURE = 125;
    static const uint8_t DHT22_MIN_HUMIDITY = 0;
    static const uint8_t DHT22_MAX_HUMIDITY = 100;

    // non-movable & non-copyable
    DHT22Sensor(const DHT22Sensor&) = delete;
    DHT22Sensor& operator=(const DHT22Sensor&) = delete;
    DHT22Sensor(DHT22Sensor&&) = delete;
    DHT22Sensor& operator=(DHT22Sensor&&) = delete;

private:
    DHT22 m_sensor;

    float m_lastHumidity = DHT22_MIN_HUMIDITY;
    float m_lastTemperature = DHT22_MAX_TEMPERATURE;

    const uint8_t m_temperatureTrigger = 10; // 10/10.0 = 1 degree sensitivity
    const uint8_t m_humidityTrigger = 50; // 50/10.0 = 5 precent sensitivity
};