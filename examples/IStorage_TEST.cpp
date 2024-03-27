#include <Arduino.h>
#include <IStorage.h>

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

TestStorage storage(32);

void setup()
{
    Serial.begin(115200);

    Serial.println("IStorage Tests");

    // read, write, read
    uint8_t x = 8;
    storage.write(1, x); // should print 8
    x = 0;
    storage.read(1, x);
    Serial.println(x);

    // read, write, read
    uint16_t y = 1234;
    storage.write(2, y);
    y = 0;
    storage.read(2, y);
    Serial.println(y);

    // read
    storage.write(2, y); // should print 1234; only once; same value, same address

    // invalid address
    uint32_t invalid = 1234; // 4 bytes go past the 32 size of storage
    if (storage.write(30, invalid))
    {
        Serial.println("Write of 4 bytes to address 30 of a storage with 32 size should fail.");
    }

    // clear
    storage.clear(0, 32);
    uint8_t buffer[32] = { 1, 2, 3, 4, 5, 6 };
    uint8_t expected[32] = { 0 };
    if (!storage.read(0, buffer) || memcmp(buffer, expected, sizeof(buffer) / sizeof(buffer[0])) != 0)
    {
        Serial.println("[FAILED]: buffer was not cleared.");
    }

    // Test template specialization for uint8_t*
    uint8_t data[] = { 10, 20, 30, 40, 50 };
    storage.write(5, data);
    uint8_t readData[5] = { 0 };
    storage.read(5, readData);
    if (memcmp(data, readData, sizeof(data)) == 0)
    {
        Serial.println("[PASSED]: uint8_t* specialization works correctly.");
    }
    else
    {
        Serial.println("[FAILED]: uint8_t* specialization does not work correctly.");
    }

    // Test template specialization for unsigned char*
    unsigned char udata[] = { 60, 70, 80, 90, 100 };
    storage.write(10, udata);
    unsigned char ureadData[5] = { 0 };
    storage.read(10, ureadData);
    if (memcmp(udata, ureadData, sizeof(udata)) == 0)
    {
        Serial.println("[PASSED]: unsigned char* specialization works correctly.");
    }
    else
    {
        Serial.println("[FAILED]: unsigned char* specialization does not work correctly.");
    }
}

void loop()
{

}