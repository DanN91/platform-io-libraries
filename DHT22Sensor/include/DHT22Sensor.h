#pragma once

#include <Arduino.h>

#include "DHT22.h"
#include "ISubject.h"

enum DHT22Mask : uint16_t
{
    Temperature = 0x01,
    Humidity = 0x02,
};

class DHT22Sensor final : public ISubject
{
public:
    DHT22Sensor(byte digitalPin, DHT22Mask mask);
    DHT22Sensor(byte digitalPin, DHT22Mask mask, byte temperatureTrigger, byte humidityTrigger);
    
    void Initialize();
    void ReadValues();

private:
    DHT22 m_sensor;
    DHT22Mask m_mask = static_cast<DHT22Mask>(DHT22Mask::Temperature | DHT22Mask::Humidity);
    float m_lastHumidity = 0;
    float m_lastTemperature = 100;
    byte m_temperatureTrigger = 10; // 10/10.0 = 1 degree sensitivity
    byte m_humidityTrigger = 50; // 50/10.0 = 5 precent sensitivity

    // non-movable & non-copyable
    DHT22Sensor(const DHT22Sensor&) = delete;
    DHT22Sensor& operator=(const DHT22Sensor&) = delete;

    DHT22Sensor(DHT22Sensor&&) = delete;
    DHT22Sensor& operator=(DHT22Sensor&&) = delete;
};