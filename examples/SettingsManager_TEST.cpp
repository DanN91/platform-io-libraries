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
            case Settings::IncubationTemperature:
                Serial.println("Temperature was changed.");
                break;

            case Settings::IncubationHumidity:
                Serial.println("Humidity was changed.");
                break;
        }
    }
};

class TestStorage : public IStorage
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
        Serial.print("Read ");
        Serial.print(dataSize);
        Serial.print(" bytes from [");
        Serial.print(address);
        Serial.println("]");

        for (uint8_t i = 0; i < dataSize; ++i)
        {
            *((uint8_t*)(&data) + i) = buffer[address + i];
        }

        return true;
    }

    bool clearBytes(uint16_t address, uint16_t count) override
    {
        for (uint8_t i = address; i < count && i < (sizeof(buffer) / sizeof(buffer[0])); ++i)
        {
            buffer[i] = 0;
        }

        return true;
    }

    uint8_t buffer[32] = { 0 };
};

uint16_t GetAddress(Settings setting)
{
	switch (setting)
	{
	case Settings::IncubationTemperature: // 8 bytes
		return 0;

	case Settings::IncubationHumidity: // 2 bytes
		return 8;

	case Settings::CycleState: // 1 byte
		return 10;

	default:
		return -1; // max uint16_t
	}
}

TestStorage memoryStorage(32);
SettingsManager settings(memoryStorage, GetAddress);
TestObserver testObserver(settings, Settings::IncubationTemperature);

struct Parameter
{
    float Min;
    float Max;

    bool operator==(const Parameter& other)
    {
        return Min == other.Min && Max == other.Max;
    }
};

void setup()
{
    Serial.begin(115200);

    Serial.println("*** READY ***");

    testObserver.Register();

    if (!settings)
    {
        Serial.println("FAILED: settings is not a valid object, AddressProviderFunc null.");
    }

    // temperature
    Parameter temperature { 12.5, 30.5 };
    settings.Set(Settings::IncubationTemperature, temperature);

    temperature = { 0, 0 };

    settings.Get(Settings::IncubationTemperature, temperature);

    if (temperature.Min != 12.5 || temperature.Max != 30.5)
    {
        Serial.println("FAILED: min and max temperature should be stored properly.");
    }

    settings.Clear(Settings::IncubationTemperature, sizeof(temperature));

    settings.Get(Settings::IncubationTemperature, temperature);

    if (temperature.Min != 0 || temperature.Max != 0)
    {
        Serial.println("FAILED: min and max temperature should have been cleared.");
    }
}

void loop()
{
    delay(1000);
}