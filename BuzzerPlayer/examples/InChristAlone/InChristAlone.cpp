/* In Christ Alone */

#include <Arduino.h>
#include <BuzzerPlayer.h>

Buzzer::BuzzerPlayer buzzer(11);

void setup()
{
    Serial.begin(115200);

    buzzer.Initialize();

    Serial.println("*** Buzzer Player Ready ***");
};

void loop()
{
    buzzer.Play(Buzzer::InChristAlone);
    delay(10000);
}