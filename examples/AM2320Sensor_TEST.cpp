#include <AM2320Sensor.h>
#include <NonBlockingDelay.h>

class Reader : public Runnable, public IObserver<AM2320SensorMask>
{
   public:
    Reader(AM2320Sensor& sensor)
      : IObserver(AM2320SensorMask::Humidity | AM2320SensorMask::Temperature, sensor)
      , m_sensor(sensor)
    {
    }

    void Run() override
    {
        Serial.println("Reading sensor values...");
        Serial.print("T: ");
        Serial.println(m_sensor.temperature());
        Serial.print("H: ");
        Serial.println(m_sensor.humidity());
        Serial.println("Done reading sensor values.");
    }

    // IObserver
    void OnEvent(AM2320SensorMask mask) override
    {
      switch (mask)
      {
          case AM2320SensorMask::Temperature:
          {
              Serial.print("T changed: ");
              Serial.println(m_sensor.temperature());
              break;
          }

          case AM2320SensorMask::Humidity:
          {
              Serial.print("H changed: ");
              Serial.println(m_sensor.humidity());
              break;
          }

          default:
              break;
      }
    }

   private:
    AM2320Sensor& m_sensor;
};

AM2320Sensor sensor(5); // 0.5 degree C change sensitivity
Reader reader(sensor);
NonBlockingDelay readingDelay(10000, reader);

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
        delay(10);  // hang out until serial port opens
    }

    Serial.println("AM2320 Basic Serial Observer Test");

    sensor.initialize();
    reader.Register();
}

void loop()
{
    readingDelay.Handle();
    sensor.handleEvents();
}