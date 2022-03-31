#include <Arduino.h>
#include <SDLogger.h>

constexpr uint8_t MICRO_SD_PIN = 4;

SDLogger logger("log.txt");
SDLogger test("test.txt");

void setup()
{
    Serial.begin(9600);

    if (!SDLogger::Initialize(MICRO_SD_PIN)) // call this once
        Serial.println("Initialization failed.");

    logger.Log("This is a log line.");
    test.Log("This is another log line in a different file.");
}

void loop()
{
}
