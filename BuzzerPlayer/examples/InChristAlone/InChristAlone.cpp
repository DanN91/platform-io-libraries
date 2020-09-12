/* In Christ Alone */

#include <Arduino.h>
#include <BuzzerPlayer.h>

BuzzerPlayer buzzer(9);

void setup()
{
    Serial.begin(57600);

    buzzer.Initialize();

    Serial.println("*** Buzzer Player Ready ***");
};

void loop()
{
    buzzer.Play(InChristAlone);
    delay(10000);
}