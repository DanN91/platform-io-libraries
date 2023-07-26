#include <Arduino.h>

#include <LEDController.h>
#include <LEDControllerComposite.h>

LEDControllerComposite RED_LEDS;

LEDController RED_1(12);
LEDController RED_2(11);
LEDController RED_3(10);
LEDController RED_4(9);
LEDController RED_5(8);

LEDControllerComposite BLUE_LEDS;

LEDController BLUE_1(7);
LEDController BLUE_2(6);
LEDController BLUE_3(5);
LEDController BLUE_4(4);
LEDController BLUE_5(3);

void setup()
{
    Serial.begin(115200);

    RED_LEDS.Add(&RED_1);
    RED_LEDS.Add(&RED_2);
    RED_LEDS.Add(&RED_3);
    RED_LEDS.Add(&RED_4);
    RED_LEDS.Add(&RED_5);

    RED_LEDS.Initialize();
    RED_LEDS.Configure(500, 2);


    BLUE_LEDS.Add(&BLUE_1);
    BLUE_LEDS.Add(&BLUE_2);
    BLUE_LEDS.Add(&BLUE_3);
    BLUE_LEDS.Add(&BLUE_4);
    BLUE_LEDS.Add(&BLUE_5);

    BLUE_LEDS.Initialize();
    BLUE_LEDS.Configure(1000, 3);

    BLUE_LEDS.Chain(&RED_LEDS);

    Serial.println("Initialized.");
}

void loop()
{
    RED_LEDS.Run();
    BLUE_LEDS.Run();
}