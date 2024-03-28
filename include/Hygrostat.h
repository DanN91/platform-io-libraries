#pragma once

#include <Arduino.h>

#include <ObserverPattern.h>
#include <ISwitch.h>

#include <DHT22Sensor.h>
#include <SettingsManager.h>

class Hygrostat final : public IObserver<DHT22Mask>, public IObserver<Settings>
{
public:
    Hygrostat(DHT22Sensor& sensor, SettingsManager& settings, ISwitch& humidifier);

    void Initialize();

    // IObserver
    void OnEvent(DHT22Mask mask) override;
    void OnEvent(Settings setting) override;

private:
    float m_onThreshold;
    float m_offThreshold;

    DHT22Sensor& m_sensor;
    SettingsManager& m_settings;

    ISwitch& m_humidifier;
};
