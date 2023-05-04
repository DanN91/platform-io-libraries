/* In Christ Alone */

#include <Arduino.h>
#include <BuzzerPlayer.h>

BuzzerPlayer buzzer(11);

void setup()
{
    Serial.begin(115200);

    buzzer.Initialize();

    Serial.println("*** Buzzer Player Ready ***");
};

void loop()
{
    buzzer.Play(InChristAlone);
    delay(10000);
}