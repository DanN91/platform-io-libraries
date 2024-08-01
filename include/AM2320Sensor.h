/*!
 * @file AM2320Sensor.h
 * @brief Header file for the AM2320Sensor class.
 *
 * This file contains the declaration of the AM2320Sensor class, which provides
 * functionality for interfacing with the AM2320 temperature and humidity sensor.
 * It includes methods for initializing the sensor, retrieving temperature and
 * humidity readings, and handling events based on configurable thresholds.
 *
 * The AM2320Sensor class is designed to notify observers when significant changes
 * in temperature or humidity occur, making it suitable for applications requiring
 * environmental monitoring.
 */
#pragma once

#include <Arduino.h>

#include <ObserverPattern.h>

#include <AM2320.h>

#include "AM2320SensorMasks.h"

class AM2320Sensor final : public IObservable<AM2320SensorMask>
{
  public:
    /*!
     * @brief Constructor for the AM2320Sensor class.
     *
     * Initializes the sensor with the specified temperature and humidity triggers.
     *
     * @param temperatureTrigger Sensitivity for temperature changes (default: 10).
     * @param humidityTrigger Sensitivity for humidity changes (default: 50).
    * @param maximumObserversCount Maximum number of observers that can be registered (default: 1).
     */
    AM2320Sensor(uint8_t temperatureTrigger = 10, uint8_t humidityTrigger = 50, uint8_t maximumObserversCount = 1);
    ~AM2320Sensor() = default;

    /*!
     * @brief Initializes the AM2320 sensor.
     *
     * @return True if the sensor was successfully initialized, otherwise false.
     */
    bool initialize();

    /*!
     * @brief Handles events based on temperature and humidity changes.
     *
     * This method checks for significant changes in temperature or humidity and
     * notifies observers if the changes exceed the configured thresholds.
     */
    void handleEvents();

    /*!
     * @brief Gets the current temperature reading from the sensor.
     *
     * @return The current temperature in degrees Celsius.
     */
    float temperature() const;

    /*!
     * @brief Gets the current humidity reading from the sensor.
     *
     * @return The current relative humidity as a percentage.
     */
    float humidity() const;

    // Device specifications
    static const int8_t MIN_TEMPERATURE = -40;
    static const int8_t MAX_TEMPERATURE = 80;
    static const uint8_t MIN_HUMIDITY = 0;
    static const uint8_t MAX_HUMIDITY = 99;

    // non-copyable & non-movable
    AM2320Sensor(const AM2320Sensor&) = delete;
    AM2320Sensor& operator=(const AM2320Sensor&) = delete;
    AM2320Sensor(AM2320Sensor&&) = delete;
    AM2320Sensor& operator=(AM2320Sensor&&) = delete;

  private:
    AM2320 m_sensor;

    float m_lastHumidity = MIN_HUMIDITY;
    float m_lastTemperature = MAX_TEMPERATURE;

    const uint8_t m_temperatureTrigger;  // 10/10.0 = 1 degree sensitivity
    const uint8_t m_humidityTrigger;     // 50/10.0 = 5 percent sensitivity
};