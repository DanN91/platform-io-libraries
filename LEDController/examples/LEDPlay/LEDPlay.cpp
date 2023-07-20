#include <Arduino.h>
#include <LEDController.h>

LEDController RED_1(3);
LEDController RED_2(4);

void setup()
{
    Serial.begin(115200);

    RED_1.Initialize();
    RED_2.Initialize();

    RED_1.Configure(500, 3);
    RED_2.Configure(250, 3);

    Serial.println("Initialized.");
}

void loop()
{
    RED_1.Run();
    RED_2.Run();
}