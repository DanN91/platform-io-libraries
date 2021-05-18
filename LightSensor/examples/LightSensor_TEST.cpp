#include <Arduino.h>

#include <LightSensor.h>

LightSensor lightSensor(A0, LightSensor::Sensitivity::Low);

void setup()
{
    Serial.begin(115200);

    Serial.println(F("Light Sensor Test"));
}

void loop()
{
    lightSensor.HandleEvents();

    Serial.println(lightSensor.Value());

    delay(200);
}