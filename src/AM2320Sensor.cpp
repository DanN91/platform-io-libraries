/*!
 * @file AM2320Sensor.cpp
 * @brief Implementation of the AM2320Sensor class, which provides an interface
 *        for interacting with the AM2320 temperature and humidity sensor.
 *
 * This file contains the implementation of the AM2320Sensor class, including
 * methods for initialization, event handling, and retrieving temperature and
 * humidity readings. The class is designed to work with a specific temperature
 * and humidity trigger threshold.
 *
 * @author Daniel Nistor
 * @date 2025
 */

#include "AM2320Sensor.h"

AM2320Sensor::AM2320Sensor(uint8_t temperatureTrigger, uint8_t humidityTrigger, uint8_t maximumObserversCount)
    : IObservable(maximumObserversCount)
    , m_temperatureTrigger(temperatureTrigger)
    , m_humidityTrigger(humidityTrigger)
{
}

bool AM2320Sensor::initialize()
{
    return m_sensor.initialize();
}

void AM2320Sensor::handleEvents()
{
    // Get sensor readings
    const float newHumidity = m_sensor.humidity();
    const float newTemperature = m_sensor.temperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(newHumidity) || newHumidity > 100.0 || newHumidity < 0.00
        || isnan(newTemperature) || newTemperature > 125.0 || newTemperature < -40.0)
    {
#ifdef DEBUG_SERIAL
        Serial.println(F("DHT22: Failed to Read values!"));
#endif
        return;
    }

    // Notify relevant observers
    const float humidityThreshold = m_humidityTrigger / 10.0;

    if ((m_lastHumidity != newHumidity)
        && (newHumidity >= (m_lastHumidity + humidityThreshold) || newHumidity <= (m_lastHumidity - humidityThreshold)))
    {
        m_lastHumidity = newHumidity;
        Notify(AM2320SensorMask::Humidity);
    }

    // Notify relevant observers
    const float temperatureThreshold = m_temperatureTrigger / 10.0;

    if ((newTemperature != m_lastTemperature)
        && (newTemperature >= (m_lastTemperature + temperatureThreshold) || newTemperature <= (m_lastTemperature - temperatureThreshold)))
    {
        m_lastTemperature = newTemperature;
        Notify(AM2320SensorMask::Temperature);
    }
}

float AM2320Sensor::temperature() const
{
    return m_sensor.temperature();
}

float AM2320Sensor::humidity() const
{
    return m_sensor.humidity();
}