/*
    SDLogger: Object-oriented way of logging data to an SD card using Observer pattern.
    Author: Daniel Nistor
    License: MIT
*/

#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#include <ObserverPattern.h>

class SDLogger final
{
public:
    SDLogger();
    ~SDLogger();

    // non-movable & non-copyable
    SDLogger(SDLogger&&) = delete;
    SDLogger& operator=(SDLogger&&) = delete;
    SDLogger(const SDLogger&) = delete;
    SDLogger& operator=(const SDLogger&) = delete;

private:
    File m_file;
};