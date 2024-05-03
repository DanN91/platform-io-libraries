/*!
 * @file TinyDHT.cpp
 *
 * @mainpage Adafruit TinyDHT Sensor Library
 *
 * @section intro_sec Introduction
 *
 * Integer version of the Adafruit DHT library for the
 * Trinket and Gemma mini microcontrollers
 *
 * @section license License
 *
 * MIT license
 *
 * @section author Author
 *
 * Written by Adafruit Industries
 * Adaptations made by Daniel Nistor to suit DHT22-specific Purposes
 */

#include "DHT22.h"

namespace
{
  // used to set how much data to take at a time. Very few reasons to change this.
  constexpr const uint8_t DATA_COUNT_PER_READ = 6;

  // how many timing transitions we need to keep track of. 2 * number bits + extra
  constexpr const auto MAX_TIMINGS = 85;
} // anonymous

DHT22::DHT22(uint8_t pin)
    : m_pin(pin)
{
}

void DHT22::Initialize()
{
  pinMode(m_pin, INPUT);
  digitalWrite(m_pin, HIGH);
}

float DHT22::TemperatureAsCelsius()
{
  if (!Read())
    return BAD_TEMP;

  float temperature = static_cast<int16_t>(m_data[2] & 0x7F) << 8 | m_data[3];
  temperature *= 0.1;

  if (m_data[2] & 0x80)
    temperature *= -1;

  return temperature;
}

float DHT22::TemperatureAsFarenheit()
{
  const auto celsius = TemperatureAsCelsius();
  if (celsius == BAD_TEMP)
    return celsius;

  return CelsiusToFarenheit(celsius);
}

float DHT22::Humidity()
{
  if (!Read())
    return BAD_HUM;

  float humidity = static_cast<uint16_t>(m_data[0]) << 8 | m_data[1]; // to allow math operations
  humidity *= 0.1;

  return humidity;
}

float DHT22::CelsiusToFarenheit(float celsius) const
{
  return (celsius * 9) / 5 + 32;
}

bool DHT22::Read()
{
  // pull the pin high and wait 250 milliseconds
  digitalWrite(m_pin, HIGH);
  delay(250);

  const auto currentTime = millis();
  if (currentTime < m_lastReadTime) // i.e. there was a rollover
    m_lastReadTime = 0;

  // use the last value if the sensor is probed more often than once / 2 seconds
  if (!m_isFirstReading && ((currentTime - m_lastReadTime) < 2000))
    return true;

  m_isFirstReading = false;
  m_lastReadTime = millis();

  m_data[0] = m_data[1] = m_data[2] = m_data[3] = m_data[4] = 0;

  // now pull it low for ~20 milliseconds
  pinMode(m_pin, OUTPUT);

  digitalWrite(m_pin, LOW);
  delay(20);
  cli();
  digitalWrite(m_pin, HIGH);
  delayMicroseconds(40);

  pinMode(m_pin, INPUT);

  // read in timings
  uint8_t lastReadState = HIGH;
  uint8_t counter = 0;
  uint8_t j = 0;
  for (auto i = 0; i < MAX_TIMINGS; i++)
  {
    counter = 0;
    while (digitalRead(m_pin) == lastReadState)
    {
      counter++;
      delayMicroseconds(1);
      if (counter == 255)
        break;
    }

    lastReadState = digitalRead(m_pin);

    if (counter == 255)
      break;

    // ignore first 3 transitions
    if ((i >= 4) && (i % 2 == 0))
    {
      // shove each bit into the storage bytes
      m_data[j / 8] <<= 1;
      if (counter > DATA_COUNT_PER_READ)
        m_data[j / 8] |= 1;
      j++;
    }
  }

  sei();

  // check we read 40 bits and that the checksum matches
  if ((j >= 40) && (m_data[4] == ((m_data[0] + m_data[1] + m_data[2] + m_data[3]) & 0xFF)))
    return true;

  return false;
}