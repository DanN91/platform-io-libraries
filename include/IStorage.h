/*
    IStorage: Interface exposing methods for storing several data types in persistency
    Author: Daniel Nistor
    License: MIT

    This class provides an interface for storing and retrieving various data types in a persistent storage.
    It includes methods for writing, reading, and clearing data at specified addresses within the storage.
    The class supports both single data elements and arrays of data elements.

    The class is designed to be extended by concrete implementations that provide the actual storage mechanism.
    The virtual methods `writeBytes`, `readBytes`, and `clearBytes` must be implemented by derived classes to
    handle the low-level storage operations.

    Template methods are provided for writing and reading different data types, including specializations for
    pointer types and arrays. These methods ensure that data is only written if it differs from the existing
    data at the specified address, which helps to avoid unnecessary writes and potentially extend the lifespan
    of the storage (as is in the case of EEPROM).

    The class also includes a method for clearing a specified range of addresses in the storage.

    Usage:
    - Extend this class and implement the virtual methods to create a concrete storage implementation.
    - Use the `write` and `read` methods to store and retrieve data of various types.
    - Use the `clear` method to reset a range of addresses in the storage.

    Example:
    class MyStorage : public IStorage
    {
    public:
        MyStorage(uint16_t size) : IStorage(size) {}

    private:
        bool writeBytes(uint16_t address, uint8_t& data, uint8_t dataSize) override
        {
            // Implement the low-level write operation
        }

        bool readBytes(uint16_t address, uint8_t& data, uint8_t dataSize) override
        {
            // Implement the low-level read operation
        }

        bool clearBytes(uint16_t address, uint16_t count) override
        {
            // Implement the low-level clear operation
        }
    };
*/

#pragma once

#include <Arduino.h>

class IStorage
{
public:
    IStorage(uint16_t sizeInBytes)
        : m_size(sizeInBytes)
    {};

    virtual ~IStorage() = default;

    template<typename T>
    bool write(uint16_t address, T data)
    {
        if (!isAddressValid(address + sizeof(data)))
            return false;

        T readData;
        if (!read(address, readData))
        {
            return false;
        }

        // avoid unnecessary writes ( might decrease memory lifespan )
        if (memcmp(&readData, &data, sizeof(data)) == 0)
        {
            return true;
        }

        return writeBytes(address, reinterpret_cast<uint8_t&>(data), sizeof(data));
    }

    template<typename T, size_t N>
    bool write(uint16_t address, T (&data)[N])
    {
        if (!isAddressValid(address + sizeof(data)))
            return false;

        T readData[N];
        if (!read(address, readData))
        {
            return false;
        }

        // avoid unnecessary writes ( might decrease memory lifespan )
        if (memcmp(readData, data, sizeof(data)) == 0)
        {
            return true;
        }

        return writeBytes(address, reinterpret_cast<uint8_t&>(data), sizeof(data));
    }

    template<typename T>
    bool read(uint16_t address, T& data)
    {
        return isAddressValid(address + sizeof(data)) && readBytes(address, reinterpret_cast<uint8_t&>(data), sizeof(data));
    }

    template<typename T, size_t N>
    bool read(uint16_t address, T (&data)[N])
    {
        return isAddressValid(address + sizeof(data)) && readBytes(address, reinterpret_cast<uint8_t&>(data), sizeof(data));
    }

    bool clear(uint16_t address, uint16_t count)
    {
        return clearBytes(address, count);
    }

private:
    bool isAddressValid(uint16_t address) const { return address >= 0 && address <= m_size; };

    virtual bool writeBytes(uint16_t address, uint8_t& data, uint8_t dataSize) = 0;
    virtual bool readBytes(uint16_t address, uint8_t& data, uint8_t dataSize) = 0;
    virtual bool clearBytes(uint16_t address, uint16_t count) = 0;

    const uint16_t m_size = 0;
};
