#include "Hygrostat.h"

#include <DHT22Sensor.h>

Hygrostat::Hygrostat(DHT22Sensor &sensor, SettingsManager &settings, ISwitch &humidifier)
    : IObserver<DHT22Mask>(DHT22Mask::Humidity, sensor)
    , IObserver<Settings>(Settings::HumidityMin | Settings::HumidityMax, settings)
    , m_sensor(sensor)
    , m_settings(settings)
    , m_humidifier(humidifier)
{
}

void Hygrostat::Initialize()
{
    m_humidifier.Off();
}

void Hygrostat::OnEvent(DHT22Mask mask)
{
    if (mask & DHT22Mask::Humidity)
    {
        const auto value = m_sensor.Humidity();

#ifdef UNO_CONFIG
        Serial.print("H: ");
        Serial.println(value);
#endif // UNO_CONFIG

        if (value < m_onThreshold)
        {
            m_humidifier.On();
        }
        else if (value > m_offThreshold)
        {
            m_humidifier.Off();
        }
    }
}

void Hygrostat::OnEvent(Settings setting)
{
    float value = 0.0;
    if (!m_settings.Get(setting, value))
        return;

    switch (setting)
    {
        case Settings::HumidityMin:
            m_onThreshold = value;
            break;

        case Settings::HumidityMax:
            m_offThreshold = value;
            break;
    }
}
