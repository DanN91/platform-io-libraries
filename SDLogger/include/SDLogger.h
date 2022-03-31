/*
    SDLogger: Object-oriented way of logging data to an SD card using Observer pattern.
    Author: Daniel Nistor
    License: MIT
*/

#pragma once

#include <Arduino.h>
#include <SPI.h>

class SDLogger final
{
public:
    SDLogger(const char* filename);
    ~SDLogger() = default;

    static bool Initialize(uint8_t pin);
    void Log(const char* message);

    // non-movable & non-copyable
    SDLogger(SDLogger&&) = delete;
    SDLogger& operator=(SDLogger&&) = delete;
    SDLogger(const SDLogger&) = delete;
    SDLogger& operator=(const SDLogger&) = delete;

private:
    const char* m_filename;
};