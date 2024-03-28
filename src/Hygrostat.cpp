#include "Hygrostat.h"

#include <DHT22Sensor.h>

Hygrostat::Hygrostat(DHT22Sensor &sensor, ISwitch &humidifier)
    : IObserver<DHT22Mask>(DHT22Mask::Humidity, sensor)
    , m_sensor(sensor)
    , m_humidifier(humidifier)
{
}

void Hygrostat::Initialize()
{
    m_humidifier.Off();
}

void Hygrostat::OnThreshold(float value)
{
    m_onThreshold = value;
}

void Hygrostat::OffThreshold(float value)
{
    m_offThreshold = value;
}

void Hygrostat::OnEvent(DHT22Mask mask)
{
    if (mask == DHT22Mask::Humidity)
    {
        const auto value = m_sensor.Humidity();

#ifdef DEBUG_SERIAL
        Serial.print("H: ");
        Serial.println(value);
#endif // DEBUG_SERIAL

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
