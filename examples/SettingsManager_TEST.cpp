// Settings Manager Subject-Observer Pattern Test
#include <SettingsManager.h>
#include <SettingsMasks.h>

class TestObserver final : public IObserver<Settings>
{
public:
    TestObserver(IObservable<Settings>& subject, Settings mask)
        : IObserver(mask, subject)
    {
    }

    virtual ~TestObserver() = default;

    // IObserver
    void OnEvent(Settings event) override
    {
        switch (event)
        {
            case Settings::TemperatureMin:
                Serial.println("Temperature MIN was changed.");
                break;

            case Settings::TemperatureMax:
                Serial.println("Temperature MAX was changed.");
                break;
        }
    }
};

class TestStorage final : public IStorage
{
public:
    TestStorage(uint16_t size): IStorage(size) {};
    ~TestStorage() = default;

private:
    bool writeBytes(uint16_t address, uint8_t& data, uint8_t dataSize) override
    {
        for (uint8_t i = 0; i < dataSize; ++i)
        {
            buffer[address + i] = *(static_cast<uint8_t*>(&data) + i);
        }

        Serial.print("Write[");
        Serial.print(address);
        Serial.println("]");

        return true;
    }

    bool readBytes(uint16_t address, uint8_t& data, uint8_t dataSize) override
    {
        for (uint8_t i = 0; i < dataSize; ++i)
        {
            *((uint8_t*)(&data) + i) = buffer[address + i];
        }

        Serial.print("Read[");
        Serial.print(address);
        Serial.println("]");

        return true;
    }

    uint8_t buffer[32] = { 0 };
};

TestStorage memoryStorage(32);
SettingsManager settings(memoryStorage, 2);
TestObserver temperatureObserver(settings, Settings::TemperatureMin | Settings::TemperatureMax);

void setup()
{
    Serial.begin(115200);

    Serial.println("*** READY ***");

    temperatureObserver.Register();

    // temperature
    float minTemperature = 12.5;
    settings.Set(Settings::TemperatureMin, minTemperature);
    float maxTemperature = 30.5;
    settings.Set(Settings::TemperatureMax, maxTemperature);

    minTemperature = maxTemperature = 0.0f;
    settings.Get(Settings::TemperatureMin, minTemperature);
    settings.Get(Settings::TemperatureMax, maxTemperature);

    if (minTemperature != 12.5 || maxTemperature != 30.5)
    {
        Serial.println("FAILED: min and max temperature should be stored properly.");
    }

    // // humidity trigger
    // for (byte i = 1; i < 6; ++i)
    // {
    //     settingsManager.SetHumidityTrigger(i);
    //     delay(500);
    // }

    // // temperature trigger
    // for (byte i = 1; i < 6; ++i)
    // {
    //     settingsManager.SetTemperatureTrigger(i);
    //     delay(500);
    // }

    // // humidity
    // for (byte i = 50; i < 54; ++i)
    // {
    //     settingsManager.SetDesiredHumidity(i);
    //     delay(500);
    // }
}

void loop()
{
    delay(1000);
}