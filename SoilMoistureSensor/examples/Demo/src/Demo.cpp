#include <Arduino.h>

#include <SoilMoistureSensor.h>
#include <MoistureObserver.h>

constexpr const uint8_t SENSOR_PIN = A0;
SoilMoistureSensor sensor(SENSOR_PIN, SoilMoistureSensor::Sensitivity::High);

MoistureObserver observer(sensor);

void setup()
{
    Serial.begin(9600);

    Serial.println("Initialized.");
}

void loop()
{
    sensor.HandleEvents();
}