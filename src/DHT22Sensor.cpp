#include "DHT22Sensor.h"

DHT22Sensor::DHT22Sensor(uint8_t pin, uint8_t MAX_OBSERVERS_COUNT)
    : IObservable(MAX_OBSERVERS_COUNT)
    , m_sensor(pin)
{
}

DHT22Sensor::DHT22Sensor(uint8_t pin, uint8_t temperatureTrigger, uint8_t humidityTrigger, uint8_t MAX_OBSERVERS_COUNT)
    : IObservable(MAX_OBSERVERS_COUNT)
    , m_sensor(pin)
    , m_temperatureTrigger(temperatureTrigger)
    , m_humidityTrigger(humidityTrigger)
{
}

void DHT22Sensor::Initialize()
{
    m_sensor.Initialize();
}

void DHT22Sensor::HandleEvents()
{
    // Get sensor readings
    const float newHumidity = m_sensor.Humidity();
    const float newTemperature = m_sensor.TemperatureAsCelsius();

    // Check if any reads failed and exit early (to try again).
    if (isnan(newHumidity) || newHumidity > 100.0 || newHumidity < 0.00
        || isnan(newTemperature) || newTemperature > 125.0 || newTemperature < -40.0)
    {
        // Serial.println(F("DHT22: Failed to Read values!"));
        return;
    }

    // Notify relevant observers
    const float humidityThreshold = m_humidityTrigger / 10.0;

    if ((m_lastHumidity != newHumidity)
        && (newHumidity >= (m_lastHumidity + humidityThreshold) || newHumidity <= (m_lastHumidity - humidityThreshold)))
    {
        m_lastHumidity = newHumidity;
        Notify(DHT22Mask::Humidity);
    }

    // Notify relevant observers
    const float temperatureThreshold = m_temperatureTrigger / 10.0;

    if ((newTemperature != m_lastTemperature)
        && (newTemperature >= (m_lastTemperature + temperatureThreshold) || newTemperature <= (m_lastTemperature - temperatureThreshold)))
    {
        m_lastTemperature = newTemperature;
        Notify(DHT22Mask::Temperature);
    }
}

float DHT22Sensor::Temperature() const
{
    return m_lastTemperature;
}

float DHT22Sensor::Humidity() const
{
    return m_lastHumidity;
}
