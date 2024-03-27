/*
    IStorage: Interface exposing methods for storing several data types in persistency
    Author: Daniel Nistor
    License: MIT
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

    template<typename T>
    bool read(uint16_t address, T& data)
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