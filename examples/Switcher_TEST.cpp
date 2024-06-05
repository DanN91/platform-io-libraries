#include <Arduino.h>

#include <Switcher.h>

Switcher test(LED_BUILTIN);

void setup()
{
    Serial.begin(115200);

    test.Initialize();

    Serial.println("Initialized");
}

void loop()
{
    test.On();
    Serial.println(test.IsOn() ? "ON" : "OFF");
    delay(1000);
    test.Off();
    Serial.println(test.IsOn() ? "ON" : "OFF");
    delay(1000);
    test.On(128); // analog write
    Serial.println(test.IsOn() ? "ON" : "OFF");
    delay(1000);
}