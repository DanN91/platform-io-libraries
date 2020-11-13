#include "DHT22Sensor.h"

DHT22Sensor::DHT22Sensor(byte digitalPin, DHT22Mask mask)
    : ISubject()
    , m_sensor(digitalPin)
    , m_mask(mask)
{
}

DHT22Sensor::DHT22Sensor(byte digitalPin, DHT22Mask mask, byte temperatureTrigger, byte humidityTrigger)
    : ISubject()
    , m_sensor(digitalPin)
    , m_mask(mask)
    , m_temperatureTrigger(temperatureTrigger)
    , m_humidityTrigger(humidityTrigger)
{
}

void DHT22Sensor::Initialize()
{
    m_sensor.Initialize();
}

void DHT22Sensor::ReadValues()
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
    const float humidityThreshold = m_humidityTrigger/10.0;
    if (newHumidity >= (m_lastHumidity + humidityThreshold)
        || newHumidity =< (m_lastHumidity - humidityThreshold))
    {
        // update humidity
        m_lastHumidity = newHumidity;

        // notify observers
        for (byte i = 0; i < MAX_OBSERVERS_COUNT; ++i)
        {
            if (m_observers[i] && m_observers[i]->IsOfInterest(DHT22Mask::Humidity))
                m_observers[i]->Update(DHT22Mask::Humidity, newHumidity);
        }
    }

    // Notify relevant observers
    const float temperatureThreshold = m_temperatureTrigger/10.0;
    if (newTemperature >= (m_lastTemperature + temperatureThreshold)
        || newTemperature =< (m_lastTemperature - temperatureThreshold))
    if (newTemperature != m_lastTemperature)
    {
        // update readings
        m_lastTemperature = newTemperature;

        // notify observers
        for (byte i = 0; i < MAX_OBSERVERS_COUNT; ++i)
        {
            if (m_observers[i] && m_observers[i]->IsOfInterest(DHT22Mask::Temperature))
                m_observers[i]->Update(DHT22Mask::Temperature, newTemperature);
        }
    }
}
