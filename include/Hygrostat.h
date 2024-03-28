#pragma once

#include <Arduino.h>

#include <ObserverPattern.h>
#include <ISwitch.h>

#include <DHT22Sensor.h>

class Hygrostat final : public IObserver<DHT22Mask>
{
public:
    Hygrostat(DHT22Sensor& sensor, ISwitch& humidifier);

    void Initialize();

    void OnThreshold(float value);
    void OffThreshold(float value);

    // IObserver
    void OnEvent(DHT22Mask mask) override;

private:
    float m_onThreshold = 0.0;
    float m_offThreshold = 0.0;

    DHT22Sensor& m_sensor;
    ISwitch& m_humidifier;
};
