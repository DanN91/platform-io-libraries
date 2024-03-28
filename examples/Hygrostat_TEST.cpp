#include <Hygrostat.h>
#include <DHT22Sensor.h>
#include <Switcher.h>

constexpr const uint8_t DHT22_PIN = 4;

DHT22Sensor dhtSensor(DHT22_PIN);
Switcher switcher(LED_BUILTIN);
Hygrostat hygrostat(dhtSensor, switcher);

void setup()
{
    Serial.begin(115200);

    switcher.Initialize();
    dhtSensor.Initialize();

    hygrostat.Initialize();
    hygrostat.Register();

    hygrostat.OnThreshold(60);
    hygrostat.OffThreshold(70);

    Serial.println("Initialized.");
}

void loop()
{
    dhtSensor.HandleEvents();
    delay(300);
}