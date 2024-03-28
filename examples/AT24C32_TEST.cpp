#include <AT24C32.h>

AT24C32 storage;

void setup()
{
    storage.Initialize();

    Serial.begin(115200);
    Serial.println("AT24C32 Tests");

    // Tests
    bool result = true;

    int x = 1234;
    storage.write(0, x);
    x = 0;
    if (!storage.read(0, x) || x != 1234)
    {
        Serial.println("[int]: FAILED");
        result &= false;
    }

    unsigned long y = 12345678;
    storage.write(0, y);
    y = 0;
    if (!storage.read(0, y) || y != 12345678)
    {
        Serial.println("[long]: FAILED");
        result &= false;
    }

    float z = 12.34;
    storage.write(0, z);
    z = 0.0;
    if (!storage.read(0, z) || z != 12.34)
    {
        Serial.println("[float]: FAILED");
        result &= false;
    }

    double w = 12.3456;
    storage.write(0, w);
    w = 0.0;
    if (!storage.read(0, z) || z != 12.3456)
    {
        Serial.println("[double]: FAILED");
        result &= false;
    }

    Serial.println(result ? "Tests PASSED" : "Tests FAILED");
}

void loop()
{
    delay(1000);
}
