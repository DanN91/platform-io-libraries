/*
DS3231_test.pde
Eric Ayars
4/11

Test/demo of read routines for a DS3231 RTC.

Turn on the serial monitor after loading this to check if things are
working as they should.

*/

#include <DS3231.h>

#include <DateTM.h>
#include <TimeTM.h>

DS3231 clock;

void setup()
{
  Serial.begin(115200);

  Serial.println("*** Clock setup initializing... ***");

  // Serial.println("Setting HH:MM::SS ...");
  // clock.SetTime(8, 0, 0);

  // Serial.println("Setting DD:MM::YY ...");
  // clock.SetDate(2, 4, 24);

  Serial.println("*** Clock set & ready ***");
}

void ReadDS3231()
{
  TimeTM time = clock.GetTime();
  DateTM date = clock.GetDate();

  byte temperature = clock.GetTemperature();

  Serial.print(date.GetDateFormatted());
  Serial.print(" | ");
  Serial.print(time.GetTimeFormatted());
  Serial.print(" | ");
  Serial.println(String(temperature) + " C");
}

void loop()
{
	// read & show time and date once every second
	ReadDS3231();
	delay(1000);
}

