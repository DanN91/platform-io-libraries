/*!
 * @file I2CDevice.h
 * @brief Implementation of the Adafruit I2C Device class for managing I2C communication.
 *
 * This file contains the implementation of the Adafruit_I2CDevice class, which provides
 * a convenient interface for interacting with I2C devices. It includes methods for
 * initializing the I2C device, reading and writing data, detecting the device on the bus,
 * and setting the I2C clock speed.
 *
 * The original source code was developed by Adafruit Industries. This version includes
 * adaptations and modifications made by Daniel Nistor to suit specific project requirements.
 */

#pragma once

#include <Arduino.h>

class I2CDevice
{
   public:
    /*!
     * @brief Constructor for creating an I2C device at a given address.
     *
     * Initializes the I2C device with the specified 7-bit I2C address and sets
     * the default buffer size based on the platform.
     *
     * @param address The 7-bit I2C address of the device.
     */
    I2CDevice(uint8_t address);
    ~I2CDevice() = default;

    uint8_t address() const;

    /*!
     * @brief Initializes the I2C device and optionally detects its presence.
     *
     * This method initializes the I2C communication and optionally scans the bus
     * to detect the device at the specified address.
     *
     * @param detectAddress Whether to attempt address detection via a scan.
     * @return True if the I2C device was successfully initialized, otherwise false.
     */
    bool initialize(bool detectAddress = true);

    /*!
     * @brief Checks if the I2C device is present on the bus.
     *
     * This method performs a basic scan to see if the device acknowledges its
     * address on the I2C bus.
     *
     * @return True if the device was detected, otherwise false.
     */
    bool wasDetected();

    /*!
     * @brief Reads data from the I2C device into a buffer.
     *
     * This method reads a specified number of bytes from the I2C device into the
     * provided buffer. If the requested data exceeds the maximum buffer size, the
     * method performs multiple reads to retrieve all the data.
     *
     * @param buffer Pointer to the buffer to store the read data.
     * @param len Number of bytes to read.
     * @param stop Whether to send an I2C STOP signal after the read.
     * @return True if the read operation was successful, otherwise false.
     */
    bool read(uint8_t* buffer, size_t len, bool stop = true);

    /*!
     * @brief Writes data to the I2C device.
     *
     * This method writes a buffer of data to the I2C device. Optionally, a prefix
     * buffer can be written before the main data buffer. The total size of the
     * data (prefix + main buffer) must not exceed the maximum buffer size.
     *
     * @param buffer Pointer to the main data buffer to write.
     * @param len Number of bytes to write from the main buffer.
     * @param stop Whether to send an I2C STOP signal after the write.
     * @param prefixBuffer Pointer to an optional prefix buffer to write before the main buffer.
     * @param prefixLen Number of bytes to write from the prefix buffer.
     * @return True if the write operation was successful, otherwise false.
     */
    bool write(const uint8_t* buffer, size_t len, bool stop = true, const uint8_t* prefixBuffer = nullptr, size_t prefixLen = 0);

    /*!
     * @brief Performs a write-then-read operation on the I2C device.
     *
     * This method writes data to the I2C device and then reads data from it into
     * another buffer. The buffers can point to the same or overlapping locations.
     *
     * @param writeBuffer Pointer to the buffer of data to write.
     * @param writeLen Number of bytes to write.
     * @param readBuffer Pointer to the buffer to store the read data.
     * @param readLen Number of bytes to read.
     * @param stop Whether to send an I2C STOP signal between the write and read.
     * @return True if the write and read operations were successful, otherwise false.
     */
    bool writeThenRead(const uint8_t* writeBuffer, size_t writeLen, uint8_t* readBuffer, size_t readLen, bool stop = false);

    /*! @brief  How many bytes we can read in a transaction
     *  @return The size of the Wire receive/transmit buffer */
    size_t maxBufferSize() const
    {
        return m_maxBufferSize;
    }

    // non-copyable & non-movable
    I2CDevice(const I2CDevice&) = delete;
    I2CDevice& operator=(const I2CDevice&) = delete;
    I2CDevice(I2CDevice&&) = delete;
    I2CDevice& operator=(I2CDevice&&) = delete;

   private:
    /*!
     * @brief Reads data from the I2C device in a single transaction.
     *
     * This method reads a specified number of bytes from the I2C device in a
     * single transaction. It is used internally by the `read` method to handle
     * individual read operations.
     *
     * @param buffer Pointer to the buffer to store the read data.
     * @param len Number of bytes to read.
     * @param stop Whether to send an I2C STOP signal after the read.
     * @return True if the read operation was successful, otherwise false.
     */
    bool readInternal(uint8_t* buffer, size_t len, bool stop);

    const uint8_t m_address;
    bool m_hasBegun = false;
    const size_t m_maxBufferSize;
};