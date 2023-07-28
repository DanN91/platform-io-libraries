#include <Arduino.h>

#include <Hardware.h>
#include <LEDController.h>
#include <LEDControllerComposite.h>
#include <LEDBlinkConfiguration.h>
#include <LEDBlinkConfigurationComposite.h>

LEDControllerComposite RED_LEDS;

LEDController RED_1(Hardware::RED_LED_1);
LEDController RED_2(Hardware::RED_LED_2);
LEDController RED_3(Hardware::RED_LED_3);
LEDController RED_4(Hardware::RED_LED_4);
LEDController RED_5(Hardware::RED_LED_5);

LEDControllerComposite BLUE_LEDS;

LEDController BLUE_1(Hardware::BLUE_LED_1);
LEDController BLUE_2(Hardware::BLUE_LED_2);
LEDController BLUE_3(Hardware::BLUE_LED_3);
LEDController BLUE_4(Hardware::BLUE_LED_4);
LEDController BLUE_5(Hardware::BLUE_LED_5);

// TEST Data
LEDBlinkConfiguration case1Config(1000, 2);

LEDBlinkConfiguration case2Config(500, 4);
LEDBlinkConfigurationComposite case2configs;

LEDBlinkConfiguration case3Config(1000, 3);

void test_setup(uint8_t index)
{
    // * Single LED TEST CASES *
    // 1. One LED, One Configuration + Reset
    // 2. One LED, Multiple Configurations + Reset
    // * Multiple LEDs TEST CASES *
    // 1. Multiple LED in Series, One Configuration + Reset
    // 2. Multiple LED in Series, Multiple Configuration + Reset
    // 3. Multiple LEDs in Parallel, One Configuration
    // 4. Multiple LEDs in Parallel, Multiple Configurations + Reset
    switch (index)
    {
        // * Single LED TEST CASES *
        case 1:
        {
            // 1. One LED, One Configuration + Reset
            RED_1.Initialize();
            RED_1.Configure(&case1Config);
            break;
        }

        case 2:
        {
            // 2. One LED, Multiple Configurations + Reset
            case2configs.Add(&case1Config);
            case2configs.Add(&case2Config);

            RED_1.Initialize();
            RED_1.Configure(&case2configs);
            break;
        }

        case 3:
        {
            // 1. Multiple LED in Series, One Configuration + Reset
            RED_1.SetName("RED_1");
            RED_2.SetName("RED_2");
            RED_3.SetName("RED_3");

            RED_LEDS.Add(&RED_1);
            RED_LEDS.Add(&RED_2);
            RED_LEDS.Add(&RED_3);

            RED_LEDS.Initialize();
            RED_LEDS.Configure(&case3Config);
            break;
        }
    }
}

bool test_run(uint8_t index)
{
    // * Single LED TEST CASES *
    // 1. One LED, One Configuration
    // 2. One LED, Multiple Configurations
    // * Multiple LEDs TEST CASES *
    // 1. Multiple LED in Series, One Configuration + Reset
    // 2. Multiple LED in Series, Multiple Configuration + Reset
    // 3. Multiple LEDs in Parallel, One Configuration
    // 4. Multiple LEDs in Parallel, Multiple Configurations + Reset
    switch (index)
    {
        // * Single LED TEST CASES *
        case 1: // One LED, One Configuration
        {
            RED_1.SafeRun();
            return RED_1.HasFinished();
        }

        case 2: // One LED, Multiple Configurations
        {
            RED_1.SafeRun();
            return RED_1.HasFinished();
        }

        case 3: // Multiple LED in Series, One Configuration
        {
            RED_LEDS.SafeRun();
            return RED_LEDS.HasFinished();
        }

        default:
        {
            Serial.println("TEST INDEX not found.");
        }
    }

    return true;
}

constexpr uint8_t testIndex = 3;

void setup()
{
    Serial.begin(115200);

    // * Single LED TEST CASES *
    // 1. One LED, One Configuration + Reset
    // 2. One LED, Multiple Configurations + Reset
    // * Multiple LEDs TEST CASES *
    // 3. Multiple LED in Series, One Configuration + Reset
    // 4. Multiple LED in Series, Multiple Configuration + Reset
    // 5. Multiple LEDs in Parallel, One Configuration
    // 6. Multiple LEDs in Parallel, Multiple Configurations + Reset
    test_setup(testIndex);
    //
    // RED_1.Initialize();
    // RED_1.Configure(&testConfig);

    // configs.Add(&testConfig);
    // configs.Add(&secondConfig);

    // RED_LEDS.Add(&RED_1);
    // RED_LEDS.Add(&RED_2);
    // RED_LEDS.Add(&RED_3);
    // RED_LEDS.Add(&RED_4);
    // RED_LEDS.Add(&RED_5);

    // RED_LEDS.Initialize();
    // RED_LEDS.Configure(&testConfig);

    // BLUE_LEDS.Add(&BLUE_1);
    // BLUE_LEDS.Add(&BLUE_2);
    // BLUE_LEDS.Add(&BLUE_3);
    // BLUE_LEDS.Add(&BLUE_4);
    // BLUE_LEDS.Add(&BLUE_5);

    // BLUE_LEDS.Initialize();
    // BLUE_LEDS.Configure(&configs);

    Serial.println("Initialized.");
}

void loop()
{
    static auto isTest = true;
    if (isTest)
    {
        if (test_run(testIndex))
        {
            Serial.println("HasFinished.");
            isTest = false;
        }
    }
    // else
    // {
    //     digitalWrite(Hardware::RED_LED_1, HIGH);
    //     digitalWrite(Hardware::RED_LED_2, HIGH);
    //     digitalWrite(Hardware::RED_LED_3, HIGH);
    //     digitalWrite(Hardware::RED_LED_4, HIGH);
    //     digitalWrite(Hardware::RED_LED_5, HIGH);

    //     digitalWrite(Hardware::BLUE_LED_1, HIGH);
    //     digitalWrite(Hardware::BLUE_LED_2, HIGH);
    //     digitalWrite(Hardware::BLUE_LED_3, HIGH);
    //     digitalWrite(Hardware::BLUE_LED_4, HIGH);
    //     digitalWrite(Hardware::BLUE_LED_5, HIGH);

    //     delay(60);

    //     digitalWrite(Hardware::RED_LED_1, LOW);
    //     digitalWrite(Hardware::RED_LED_2, LOW);
    //     digitalWrite(Hardware::RED_LED_3, LOW);
    //     digitalWrite(Hardware::RED_LED_4, LOW);
    //     digitalWrite(Hardware::RED_LED_5, LOW);

    //     digitalWrite(Hardware::BLUE_LED_1, LOW);
    //     digitalWrite(Hardware::BLUE_LED_2, LOW);
    //     digitalWrite(Hardware::BLUE_LED_3, LOW);
    //     digitalWrite(Hardware::BLUE_LED_4, LOW);
    //     digitalWrite(Hardware::BLUE_LED_5, LOW);

    //     delay(60);

    //     digitalWrite(Hardware::RED_LED_1, HIGH);
    //     digitalWrite(Hardware::RED_LED_2, HIGH);
    //     digitalWrite(Hardware::RED_LED_3, HIGH);
    //     digitalWrite(Hardware::RED_LED_4, HIGH);
    //     digitalWrite(Hardware::RED_LED_5, HIGH);

    //     delay(60);

    //     digitalWrite(Hardware::RED_LED_1, LOW);
    //     digitalWrite(Hardware::RED_LED_2, LOW);
    //     digitalWrite(Hardware::RED_LED_3, LOW);
    //     digitalWrite(Hardware::RED_LED_4, LOW);
    //     digitalWrite(Hardware::RED_LED_5, LOW);

    //     delay(60);

    //     digitalWrite(Hardware::RED_LED_1, HIGH);
    //     digitalWrite(Hardware::RED_LED_2, HIGH);
    //     digitalWrite(Hardware::RED_LED_3, HIGH);
    //     digitalWrite(Hardware::RED_LED_4, HIGH);
    //     digitalWrite(Hardware::RED_LED_5, HIGH);

    //     delay(60);

    //     digitalWrite(Hardware::RED_LED_1, LOW);
    //     digitalWrite(Hardware::RED_LED_2, LOW);
    //     digitalWrite(Hardware::RED_LED_3, LOW);
    //     digitalWrite(Hardware::RED_LED_4, LOW);
    //     digitalWrite(Hardware::RED_LED_5, LOW);

    //     delay(60);

    //     digitalWrite(Hardware::BLUE_LED_1, HIGH);
    //     digitalWrite(Hardware::BLUE_LED_2, HIGH);
    //     digitalWrite(Hardware::BLUE_LED_3, HIGH);
    //     digitalWrite(Hardware::BLUE_LED_4, HIGH);
    //     digitalWrite(Hardware::BLUE_LED_5, HIGH);

    //     delay(60);

    //     digitalWrite(Hardware::BLUE_LED_1, LOW);
    //     digitalWrite(Hardware::BLUE_LED_2, LOW);
    //     digitalWrite(Hardware::BLUE_LED_3, LOW);
    //     digitalWrite(Hardware::BLUE_LED_4, LOW);
    //     digitalWrite(Hardware::BLUE_LED_5, LOW);

    //     delay(60);

    //     digitalWrite(Hardware::BLUE_LED_1, HIGH);
    //     digitalWrite(Hardware::BLUE_LED_2, HIGH);
    //     digitalWrite(Hardware::BLUE_LED_3, HIGH);
    //     digitalWrite(Hardware::BLUE_LED_4, HIGH);
    //     digitalWrite(Hardware::BLUE_LED_5, HIGH);

    //     delay(60);

    //     digitalWrite(Hardware::BLUE_LED_1, LOW);
    //     digitalWrite(Hardware::BLUE_LED_2, LOW);
    //     digitalWrite(Hardware::BLUE_LED_3, LOW);
    //     digitalWrite(Hardware::BLUE_LED_4, LOW);
    //     digitalWrite(Hardware::BLUE_LED_5, LOW);

    //     delay(60);

    //     digitalWrite(Hardware::BLUE_LED_1, HIGH);
    //     digitalWrite(Hardware::BLUE_LED_2, HIGH);
    //     digitalWrite(Hardware::BLUE_LED_3, HIGH);
    //     digitalWrite(Hardware::BLUE_LED_4, HIGH);
    //     digitalWrite(Hardware::BLUE_LED_5, HIGH);

    //     delay(60);

    //     digitalWrite(Hardware::BLUE_LED_1, LOW);
    //     digitalWrite(Hardware::BLUE_LED_2, LOW);
    //     digitalWrite(Hardware::BLUE_LED_3, LOW);
    //     digitalWrite(Hardware::BLUE_LED_4, LOW);
    //     digitalWrite(Hardware::BLUE_LED_5, LOW);

    //     delay(60);
    // }
}