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
constexpr const uint8_t BAD_TEMP = -1; //!< Bad temperature reading

class DHT22 final
{
public:
  explicit DHT22(uint8_t pin);

  void Initialize();

  uint8_t TemperatureAsCelsius();
  uint8_t TemperatureAsFarenheit();

  uint8_t Humidity();

private:
  bool Read();

  uint8_t CelsiusToFarenheit(uint8_t celsius) const;

  bool m_isFirstReading = true;
  uint32_t m_lastReadTime = 0;

  const uint8_t m_pin;
  uint8_t m_data[6] = {};
};