/*
 * DS3231.cpp: DS3231 Real-Time Clock library
 * original code by
 * Eric Ayars
 * 4/1/11
 * 
 * updated to Arduino 1.0 
 * John Hubert
 * Feb 7, 2012
 * 
 * Released into the public domain.
 * 
 * Adapted to current form by Daniel Nistor
*/

#include <Wire.h>
#include <DS3231.h>

constexpr uint8_t CLOCK_ADDRESS = 0x68;

// Constructor
DS3231::DS3231()
{
	Wire.begin();
}

TimeTM DS3231::GetTime() const
{
	Wire.beginTransmission(CLOCK_ADDRESS);
	Wire.write(uint8_t(0x00));
	Wire.endTransmission();

	RequestBytes(3);

	const uint8_t second = BinaryToDecimal(Wire.read());
	const uint8_t minute = BinaryToDecimal(Wire.read());
	const uint8_t hour = BinaryToDecimal(Wire.read() & 0b00111111);

	return { hour, minute, second };
}

uint8_t DS3231::GetSecond() const
{
	Wire.beginTransmission(CLOCK_ADDRESS);
	Wire.write(uint8_t(0x00));
	Wire.endTransmission();

	RequestBytes(1);
	return BinaryToDecimal(Wire.read());
}

uint8_t DS3231::GetMinute() const
{
	Wire.beginTransmission(CLOCK_ADDRESS);
	Wire.write(0x01);
	Wire.endTransmission();

	RequestBytes(1);
	return BinaryToDecimal(Wire.read());
}

uint8_t DS3231::GetHour24() const
{
	Wire.beginTransmission(CLOCK_ADDRESS);
	Wire.write(0x02);
	Wire.endTransmission();

	RequestBytes(1);
	return BinaryToDecimal(Wire.read() & 0b00111111); // 24h
}

bool DS3231::SetTime(uint8_t hour, uint8_t minute, uint8_t second)
{
	return SetTime(TimeTM(hour, minute, second));
}

bool DS3231::SetTime(const TimeTM& time)
{
	if (!time)
		return false;

	WriteCommand(0x02, time.GetHour24() & 0b10111111);
	WriteCommand(0x01, time.GetMinute());
	WriteCommand(0x00, time.GetSecond());

	// This function also resets the Oscillator Stop Flag, which is set whenever power is interrupted.
	WriteControlByte((ReadControlByte(1) & 0b01111111), 1);

	return true;
}

DateTM DS3231::GetDate() const
{
	Wire.beginTransmission(CLOCK_ADDRESS);
	Wire.write(uint8_t(0x04));
	Wire.endTransmission();

	RequestBytes(3);

	const uint8_t day = BinaryToDecimal(Wire.read());
	const uint8_t month = BinaryToDecimal(Wire.read() & 0b01111111); // 21 century
	const uint8_t year = BinaryToDecimal(Wire.read());

	return DateTM(day, month, year);
}

uint8_t DS3231::GetDay() const
{
	Wire.beginTransmission(CLOCK_ADDRESS);
	Wire.write(uint8_t(0x04));
	Wire.endTransmission();

	RequestBytes(1);
	return BinaryToDecimal(Wire.read());
}

uint8_t DS3231::GetMonth() const
{
	Wire.beginTransmission(CLOCK_ADDRESS);
	Wire.write(uint8_t(0x05));
	Wire.endTransmission();

	RequestBytes(1);
	return (BinaryToDecimal(Wire.read() & 0b01111111));
}

uint8_t DS3231::GetYear() const
{
	Wire.beginTransmission(CLOCK_ADDRESS);
	Wire.write(uint8_t(0x06));
	Wire.endTransmission();

	RequestBytes(1);
	return BinaryToDecimal(Wire.read());
}

bool DS3231::SetDate(uint8_t day, uint8_t month, uint8_t year)
{
	return SetDate(DateTM(day, month, year));
}

bool DS3231::SetDate(const DateTM& date)
{
	if (!date)
		return false;

	WriteCommand(0x04, date.GetDay());
	WriteCommand(0x05, date.GetMonth());
	WriteCommand(0x06, date.GetYear(true));

	return true;
}

float DS3231::GetTemperature()
{
	// Checks the internal thermometer on the DS3231 and returns the 
	// temperature as a floating-point value.
	Wire.beginTransmission(CLOCK_ADDRESS);
	Wire.write(uint8_t(0x11));
	Wire.endTransmission();

	RequestBytes(2);
	uint8_t temp = Wire.read();	// Here's the MSB
	return float(temp) + 0.25 * (Wire.read() >> 6);
}

bool DS3231::CheckOscillator()
{
	// Returns false if the oscillator has been off for some reason.
	// If this is the case, the time is probably not correct.
	return !(ReadControlByte(1) & 0b10000000);
}

/***************************************** 
	Private Functions
 *****************************************/
uint8_t DS3231::DecimalToBinary(uint8_t val)
{
	return ((val / 10 * 16) + (val % 10));
}

uint8_t DS3231::BinaryToDecimal(uint8_t val)
{
	return ( (val / 16 * 10) + (val % 16) );
}

uint8_t DS3231::ReadControlByte(bool which)
{
	// first uint8_t (0) is 0x0e, second (1) is 0x0f
	Wire.beginTransmission(CLOCK_ADDRESS);
	Wire.write((which) ? uint8_t(0x0f) : uint8_t(0x0e));
	Wire.endTransmission();

	RequestBytes(1);
	return Wire.read();
}

void DS3231::WriteControlByte(uint8_t control, bool which)
{
	// which = false -> 0x0e, true -> 0x0f.
	Wire.beginTransmission(CLOCK_ADDRESS);
	Wire.write((which) ? uint8_t(0x0f) : uint8_t(0x0e));
	Wire.write(control);
	Wire.endTransmission();
}

void DS3231::WriteCommand(uint8_t command, uint8_t data)
{
	Wire.beginTransmission(CLOCK_ADDRESS);
	Wire.write(command);
	Wire.write(DecimalToBinary(data));
	Wire.endTransmission();
}

void DS3231::RequestBytes(uint8_t n) const
{
	Wire.requestFrom(CLOCK_ADDRESS, n);
}