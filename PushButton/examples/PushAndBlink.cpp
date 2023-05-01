#include <Arduino.h>
#include "Blinker.h"

const uint8_t BUTTON_PIN = 0;
const uint8_t LED_PIN = 1;

PushButton button(0, BUTTON_PIN);
Blinker blinker(button, LED_PIN);

void setup()
{
    blinker.Initialize();
    button.Initialize();

    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);
}

void loop()
{
    button.HandleEvents();
}