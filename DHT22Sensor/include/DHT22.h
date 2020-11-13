/*  Tiny DHT22 library
    Uses integer math to save space on Trinket/Gemma

    MIT license
    written by Adafruit Industries

    Adaptations made by Daniel Nistor to suit DHT22-specific Purposes and OOP Design
*/
#pragma once

#include <Arduino.h>

// NAN code in DHT library takes space, define bad values here
constexpr const uint8_t BAD_HUM = -1; //!< Bad humitidy reading
constexpr const auto BAD_TEMP = -999; //!< Bad temperature reading

/*
 * @brief Class that stores the state and functions for the DHT
 */
class DHT22 final
{
public:
  /*!
   * @brief DHT22 constructor
   * @param pin Pin connected to the DHT22 data pin in connection with a 10k pull-up resistor
   */
  explicit DHT22(uint8_t pin);

  /*!
   * @brief Begins connection with device
   */
  void Initialize();

  /*!
   * @brief Reads the temperature from device as Celsius
   * @return Returns the temperature;
   */
  int16_t TemperatureAsCelsius();

  /*!
   * @brief Reads the temperature from device as Farenheit
   * @return Returns the temperature
   */
  int16_t TemperatureAsFarenheit();

  /*!
   * @brief Reads the humidity from the device
   * @return Returns the humidity read from the device
   */
  uint8_t Humidity();

private:
  /*!
   * @brief Converts Celsius to Fahrenheit
   * @param celsius Degrees celsius
   * @return Returns the inputted degrees converted to Fahrenheit
   */
  int16_t CelsiusToFarenheit(int16_t celsius) const;

  /*!
   * @brief Reads data from the sensor
   * @return Returns true if the sensor data was read successfuly
   */
  bool read();

  bool m_isFirstReading = true;
  const uint8_t m_pin;
  uint32_t m_lastReadTime = 0;

  uint8_t m_data[6] = {};
};