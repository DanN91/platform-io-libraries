/*
 * DS3231.h
 *
 * Arduino Library for the DS3231 Real-Time Clock chip
 *
 * (c) Eric Ayars
 * 4/1/11
 * Updated to Arduino 1.0 By john Hubert
 * Feb 7 2012
 * released into the public domain. If you use this, please let me know
 * (just out of pure curiosity!) by sending me an email:
 * eric@ayars.org
 *
 * Adapted to current form by Daniel Nistor
 */

#pragma once

#include <Arduino.h>

#include <TimeTM.h>
#include <DateTM.h>

class DS3231 final
{
public:
	// Constructor
	DS3231();
	~DS3231() = default;

	/* Time-retrieval functions */
	// Get Time
	TimeTM GetTime() const;

	uint8_t GetSecond();
	uint8_t GetMinute();
	uint8_t GetHour24();

	// Set Time
	void SetTime(uint8_t hour, uint8_t minute, uint8_t second);

	void SetSecond(uint8_t second);
	void SetMinute(uint8_t minute);
	void SetHour24(uint8_t hour);

	// Get Date
	DateTM GetDate();

	uint8_t GetDay();
	uint8_t GetMonth();
	uint8_t GetYear(); // Last 2 digits only

	// Set Date
	bool SetDate(uint8_t day, uint8_t month, uint8_t year);

	void SetDay(uint8_t day);
	void SetMonth(uint8_t month);
	void SetYear(uint8_t year); // Last two digits of the year

	// Temperature function
	float GetTemperature();

	// Checks the status of the OSF (Oscillator Stop Flag)
	// If false, then the clock is probably not giving you the correct time
	// The OSF is cleared by function setSecond()
	bool CheckOscillator();

	// non-copyable & non-movable
	DS3231(const DS3231&) = delete;
	DS3231& operator=(const DS3231&) = delete;
	DS3231(DS3231&&) = delete;
	DS3231& operator=(DS3231&&) = delete;

private:
	static uint8_t DecimalToBinary(uint8_t decimal);
	static uint8_t BinaryToDecimal(uint8_t binary);

	// Read from the selected control uint8_t: false -> 0x0e, true -> 0x0f
	uint8_t ReadControlByte(bool which);
	// Write to the selected control uint8_t: false -> 0x0e, true -> 0x0f
	void WriteControlByte(uint8_t control, bool which);

	// Used to set/read from clock registries
	void WriteCommand(uint8_t command, uint8_t data);
	void RequestBytes(uint8_t count) const;
};
