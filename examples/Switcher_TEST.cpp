#include <Arduino.h>

#include <Switcher.h>

Switcher test(LED_BUILTIN);

void setup()
{
    test.Initialize();
}

void loop()
{
    test.On();
    delay(1000);
    test.Off();
    delay(1000);
}