/*!
 * @file AM2320.cpp
 * @brief Interface for the AM2320 temperature and humidity sensor.
 *
 * This file provides the class definition for interacting with the AM2320
 * sensor over I2C. It includes methods for initializing the sensor and
 * retrieving temperature and humidity readings.
 *
 * The original source code was developed by Limor Fried for Adafruit Industries.
 * This version includes adaptations and modifications made by Daniel Nistor to suit specific project requirements.
 */

#include <AM2320.h>

namespace
{
    constexpr uint8_t AM2320_I2C_ADDRESS = 0x5C;  // I2C address of the AM2320 sensor
    constexpr uint8_t AM2320_SENSOR_VERSION = 1;  // the sensor version
    constexpr uint8_t AM2320_CMD_READ_REG = 0x03;  // read register command
    constexpr uint8_t AM2320_REG_TEMP_H = 0x02;   // temp register address
    constexpr uint8_t AM2320_REG_HUM_H = 0x00;    // humidity register address
}  // anonymous namespace

AM2320::AM2320()
    : m_i2cDevice(AM2320_I2C_ADDRESS)
{
}

bool AM2320::initialize()
{
    if (!m_i2cDevice.initialize(false))
    {
        return false;
    }

    m_i2cDevice.wasDetected();         // Wake up the sensor
    delay(10);                         // Wait for the sensor to be ready
    return m_i2cDevice.wasDetected();  // Check if the sensor is detected
}

float AM2320::temperature() const
{
    uint32_t data = readRegister32(AM2320_REG_HUM_H);
    if (data == 0xFFFFFFFF)
    {
        return NAN;
    }

    float value = 0.0f;

    // check sign bit - the temperature MSB is signed , bit 0-15 are magnitude
    if (data & 0x8000)
    {
        value = -static_cast<int16_t>(data & 0x7FFF);
    }
    else
    {
        value = static_cast<int16_t>(data & 0xFFFF);
    }

    return value / 10.0;
}

float AM2320::humidity() const
{
    const auto data = readRegister32(AM2320_REG_HUM_H);
    if (data == 0xFFFFFFFF)
    {
        return NAN;
    }

    return (data >> 16) / 10.0;
}

uint32_t AM2320::readRegister32(uint8_t registerAddress) const
{
    uint8_t buffer[8] = {0};  // Buffer to hold the data
    bool written = false;

    // Wake up the sensor
    for (int i = 0; i < 3; i++)
    {
        written = m_i2cDevice.write(buffer, 1);
        if (written)
        {
            break;
        }

        delay(100);  // Retry delay
    }

    if (!written)
    {
        return 0xFFFFFFFF;  // No acknowledgment
    }

    delay(10);  // Wait for the sensor to be ready

    // Send a command to read the register
    buffer[0] = AM2320_CMD_READ_REG;
    buffer[1] = registerAddress;
    buffer[2] = 4;  // Read 4 bytes

    for (int i = 0; i < 3; i++)
    {
        written = m_i2cDevice.write(buffer, 3);
        if (written)
        {
            break;
        }

        delay(5);  // Retry delay
    }

    if (!written)
    {
        return 0xFFFFFFFF;  // Read command not acknowledged
    }

    delay(2);  // Wait for the sensor to process the command

    // Read the response: 2 bytes preamble, 4 bytes data, 2 bytes CRC
    if (!m_i2cDevice.read(buffer, 8))
    {
        return 0xFFFFFFFF;  // Read failed
    }

    // Validate the response
    if (buffer[0] != 0x03 || buffer[1] != 4)
    {
        return 0xFFFFFFFF;  // Invalid response
    }

    // Verify the CRC
    uint16_t receivedCrc = (buffer[7] << 8) | buffer[6];
    uint16_t calculatedCrc = crc16(buffer, 6);  // Preamble + data
    if (receivedCrc != calculatedCrc)
    {
        return 0xFFFFFFFF;  // CRC mismatch
    }

    // Combine the 4 bytes of data into a 32-bit value
    uint32_t result = (static_cast<uint32_t>(buffer[2]) << 24) | (static_cast<uint32_t>(buffer[3]) << 16) |
                      (static_cast<uint32_t>(buffer[4]) << 8) | static_cast<uint32_t>(buffer[5]);

    return result;
}

uint16_t AM2320::crc16(uint8_t* buffer, uint8_t bufferSize) const
{
    uint16_t crc = 0xFFFF; // Initial CRC value

    for (uint8_t i = 0; i < bufferSize; i++)
    {
        crc ^= buffer[i]; // XOR byte into least significant byte of CRC

        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & 0x0001)
            {
                crc >>= 1;
                crc ^= 0xA001; // Polynomial used in Modbus CRC
            }
            else
            {
                crc >>= 1;
            }
        }
    }

    return crc;
}