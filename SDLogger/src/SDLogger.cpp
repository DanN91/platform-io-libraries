/*
    SDLogger: Object-oriented way of logging data to an SD card using Observer pattern.
    Author: Daniel Nistor
    License: MIT
*/

#include "SDLogger.h"

#include <SD.h>

SDLogger::SDLogger(const char *filename)
    : m_filename(filename)
{
}

bool SDLogger::Initialize(uint8_t pin)
{
    return SD.begin(pin);
}

void SDLogger::Log(const char* message)
{
    // open the file. note that only one file can be open at a time
    if (auto file = SD.open(m_filename, FILE_WRITE | O_APPEND); file)
    {
        file.println(message);
        file.close(); // so we close it here to allow having multiple SDLogger instances.
    }
    else
    {
        Serial.println("Could not log message.");
    }
}
