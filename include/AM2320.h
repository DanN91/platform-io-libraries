/*!
 * @file AM2320.h
 * @brief Interface for the AM2320 temperature and humidity sensor.
 *
 * This file provides the class definition for interacting with the AM2320
 * sensor over I2C. It includes methods for initializing the sensor and
 * retrieving temperature and humidity readings.
 *
 * The original source code was developed by Limor Fried for Adafruit Industries.
 * This version includes adaptations and modifications made by Daniel Nistor to suit specific project requirements.
 */

#pragma once

#include <I2CDevice.h>

class AM2320
{
  public:
    /*!
     * @brief Constructor for the AM2320 sensor.
     *
     * Initializes the I2C device for communication with the AM2320 sensor.
     */
    AM2320();

    /*!
     * @brief Destructor for the AM2320 sensor.
     */
    ~AM2320() = default;

    /*!
     * @brief Initializes the AM2320 sensor.
     *
     * This method initializes the I2C communication with the sensor and
     * prepares it for reading temperature and humidity data.
     *
     * @return True if the sensor was successfully initialized, otherwise false.
     */
    bool initialize();

    /*!
     * @brief Reads the temperature from the AM2320 sensor.
     *
     * @return The temperature in degrees Celsius as a floating-point value.
     */
    float temperature() const;

    /*!
     * @brief Reads the humidity from the AM2320 sensor.
     *
     * @return The relative humidity as a percentage (0-100%) as a floating-point value.
     */
    float humidity() const;

    // non-copyable & non-movable
    AM2320(const AM2320&) = delete;            // Copy constructor
    AM2320& operator=(const AM2320&) = delete; // Copy assignment operator
    AM2320(AM2320&&) = delete;                 // Move constructor
    AM2320& operator=(AM2320&&) = delete;      // Move assignment operator

  private:
    /*!
     * @brief Reads a 32-bit value from the specified register of the AM2320 sensor.
     *
     * @param registerAddress The register address to read from.
     * @return The 32-bit value read from the specified register.
     */
    uint32_t readRegister32(uint8_t registerAddress) const;

    /*!
     * @brief Calculates the CRC16 checksum for a given buffer.
     *
     * This method computes the CRC16 checksum using the provided buffer and its length.
     * It is typically used for data integrity verification in communication protocols.
     *
     * @param buffer Pointer to the buffer containing the data.
     * @param bufferSize Number of bytes in the buffer.
     * @return The computed CRC16 checksum as a 16-bit unsigned integer.
     */
    uint16_t crc16(uint8_t* buffer, uint8_t bufferSize) const;

    /*!
     * @brief I2C device instance for communication with the AM2320 sensor.
     */
    mutable I2CDevice m_i2cDevice;
};