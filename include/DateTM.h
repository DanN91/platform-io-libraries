/*
 *	DateTM - Library for storing date.
*/

#pragma once

#include <Arduino.h>

enum Month : uint8_t
{
	January = 1,
	February,
	March,
	April,
	May,
	June,
	July,
	August,
	September,
	October,
	November,
	December,
	MONTH_COUNT
};

class DateTM final
{
public:
	DateTM(uint8_t day, uint8_t month, uint8_t year);
	DateTM() = default;
	~DateTM() = default;

	bool SetDay(uint8_t day);
	bool SetMonth(uint8_t month);
	bool SetYear(uint8_t year);

	bool SetDate(uint8_t day, uint8_t month, uint8_t year);

	uint8_t GetDay() const;
	uint8_t GetMonth() const;
	uint16_t GetYear(bool useShortVersion = false) const;

	// Date Math
	bool AddDays(uint8_t days);

	String GetDateFormatted() const;

	friend bool operator == (const DateTM& lhs, const DateTM& rhs);
	friend bool operator >= (const DateTM& lhs, const DateTM& rhs);

	explicit operator bool() const;

	// copyable and movable, default impl
	DateTM(const DateTM&) = default;
	DateTM& operator=(const DateTM&) = default;
	DateTM(DateTM&&) = default;
	DateTM& operator=(DateTM&&) = default;

private:
	// default date is 1st of January 2000
	bool IsLeapYear(uint16_t year) const;
	bool IsDateValid(uint8_t day, uint8_t month, uint8_t year) const;

	uint8_t GetValidMaxDay(Month month, uint16_t year) const;

	uint8_t m_day = 255;
	Month m_month = Month::January;
	uint8_t m_year = 0;
};
