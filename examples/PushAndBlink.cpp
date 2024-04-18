#include <Arduino.h>
#include "Blinker.h"

const uint8_t BUTTON_PIN = 7;

PushButton button(BUTTON_PIN);
Blinker blinker(button, LED_BUILTIN);

void setup()
{
    Serial.begin(115200);

    blinker.Initialize();
    button.Initialize();

    blinker.Register();

    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);

    Serial.println("Initialized");
}

void loop()
{
    button.HandleEvents();
}