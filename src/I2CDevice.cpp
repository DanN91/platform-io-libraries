/*!
 * @file I2CDevice.cpp
 * @brief Implementation of the Adafruit I2C Device class for managing I2C
 * communication.
 *
 * This file contains the implementation of the I2CDevice class, which provides
 * a convenient interface for interacting with I2C devices. It includes methods
 * for initializing the I2C device, reading and writing data, detecting the
 * device on the bus, and setting the I2C clock speed.
 *
 * The original source code was developed by Adafruit Industries. This version
 * includes adaptations and modifications made by Daniel Nistor to suit specific
 * project requirements.
 */

#include "I2CDevice.h"

#include <Wire.h>

I2CDevice::I2CDevice(uint8_t address)
    : m_address(address),
// Set the default I2C buffer size based on the platform
// This is necessary for the fact that some platforms have different buffer sizes
#ifdef ESP32
      m_maxBufferSize(I2C_BUFFER_LENGTH)
#else
      m_maxBufferSize(32)
#endif
{
}

bool I2CDevice::initialize(bool detectAddress)
{
    Wire.begin();
    m_hasBegun = true;

    if (detectAddress)
    {
        return wasDetected();
    }

    return m_hasBegun;
}

bool I2CDevice::wasDetected()
{
    // A basic scanner, see if it ACK's
    Wire.beginTransmission(m_address);

#ifdef DEBUG_SERIAL
    Serial.print(F("Address 0x"));
    Serial.print(m_address, HEX);
#endif

    if (Wire.endTransmission() == 0)
    {
#ifdef DEBUG_SERIAL
        Serial.println(F(" Detected"));
#endif

        return true;
    }

#ifdef DEBUG_SERIAL
    Serial.println(F(" Not detected"));
#endif

    return false;
}

bool I2CDevice::write(const uint8_t *buffer, size_t len, bool stop, const uint8_t *prefixBuffer, size_t prefixLen)
{
    if ((len + prefixLen) > maxBufferSize())
    {
        // currently not guaranteed to work if more than 32 bytes!
        // we will need to find out if some platforms have larger
        // I2C buffer sizes :/
#ifdef DEBUG_SERIAL
        Serial.println(F("\tI2CDevice could not write such a large buffer"));
#endif
        return false;
    }

    Wire.beginTransmission(m_address);

    // Write the prefix data (usually an address)
    if ((prefixLen != 0) && (prefixBuffer != nullptr))
    {
        if (Wire.write(prefixBuffer, prefixLen) != prefixLen)
        {
#ifdef DEBUG_SERIAL
            Serial.println(F("\tI2CDevice failed to write"));
#endif
            return false;
        }
    }

    // Write the data itself
    if (Wire.write(buffer, len) != len)
    {
#ifdef DEBUG_SERIAL
        Serial.println(F("\tI2CDevice failed to write"));
#endif
        return false;
    }

#ifdef DEBUG_SERIAL
    Serial.print(F("\tI2CWRITE @ 0x"));
    Serial.print(m_address, HEX);
    Serial.print(F(" :: "));
    if ((prefixLen != 0) && (prefixBuffer != nullptr))
    {
        for (uint16_t i = 0; i < prefixLen; i++)
        {
            Serial.print(F("0x"));
            Serial.print(prefixBuffer[i], HEX);
            Serial.print(F(", "));
        }
    }

    for (uint16_t i = 0; i < len; i++)
    {
        Serial.print(F("0x"));
        Serial.print(buffer[i], HEX);
        Serial.print(F(", "));

        if (i % 32 == 31)
        {
            Serial.println();
        }
    }

    if (stop)
    {
        Serial.print("\tSTOP");
    }
#endif

    if (Wire.endTransmission(stop) == 0)
    {
#ifdef DEBUG_SERIAL
        Serial.println();
        // Serial.println(F("Sent!"));
#endif
        return true;
    }
    else
    {
#ifdef DEBUG_SERIAL
        Serial.println("\tFailed to send!");
#endif
        return false;
    }
}

bool I2CDevice::read(uint8_t *buffer, size_t len, bool stop)
{
    size_t pos = 0;

    while (pos < len)
    {
        const size_t readLen = ((len - pos) > maxBufferSize()) ? maxBufferSize() : (len - pos);
        const bool stopReading = (pos < (len - readLen)) ? false : stop;
        if (!readInternal(buffer + pos, readLen, stopReading))
        {
            return false;
        }

        pos += readLen;
    }

    return true;
}

bool I2CDevice::readInternal(uint8_t *buffer, size_t len, bool stop)
{
#if defined(TinyWireM_h)
    size_t recv = Wire.requestFrom((uint8_t)m_address, (uint8_t)len);
#else
    size_t recv = Wire.requestFrom((uint8_t)m_address, (uint8_t)len, (uint8_t)stop);
#endif

    if (recv != len)
    {
        // Not enough data available to fulfill our obligation!
#ifdef DEBUG_SERIAL
        Serial.print(F("\tI2CDevice did not receive enough data: "));
        Serial.println(recv);
#endif
        return false;
    }

    for (uint16_t i = 0; i < len; i++)
    {
        buffer[i] = Wire.read();
    }

#ifdef DEBUG_SERIAL
    Serial.print(F("\tI2CREAD  @ 0x"));
    Serial.print(m_address, HEX);
    Serial.print(F(" :: "));

    for (uint16_t i = 0; i < len; i++)
    {
        Serial.print(F("0x"));
        Serial.print(buffer[i], HEX);
        Serial.print(F(", "));

        if (len % 32 == 31)
        {
            Serial.println();
        }
    }

    Serial.println();
#endif

    return true;
}

bool I2CDevice::writeThenRead(const uint8_t *writeBuffer, size_t writeLen, uint8_t *readBuffer, size_t readLen, bool stop)
{
    if (!write(writeBuffer, writeLen, stop))
    {
        return false;
    }

    return read(readBuffer, readLen);
}

uint8_t I2CDevice::address() const
{
    return m_address;
}