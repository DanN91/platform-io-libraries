/*
 *	TimeTM - Library for storing time in 24h format.
*/

#pragma once

#include <Arduino.h>

class TimeTM final
{
public:
	TimeTM(uint8_t hour, uint8_t minute, uint8_t second);
	TimeTM() = default;
	~TimeTM() = default;

	bool SetHour24(uint8_t hour);
	bool SetMinute(uint8_t minute);
	bool SetSecond(uint8_t second);

	bool SetTime(uint8_t hour, uint8_t minute, uint8_t second);

	uint8_t GetHour24() const;
	uint8_t GetMinute() const;
	uint8_t GetSecond() const;

	String GetTimeFormatted() const;

	friend bool operator == (const TimeTM& lhs, const TimeTM& rhs);
	friend bool operator >= (const TimeTM& lhs, const TimeTM& rhs);

	explicit operator bool() const;

	// copyable and movable, default impl
	TimeTM(const TimeTM&) = default;
	TimeTM& operator=(const TimeTM&) = default;
	TimeTM(TimeTM&&) = default;
	TimeTM& operator=(TimeTM&&) = default;

private:
	bool IsTimeValid(uint8_t hour, uint8_t minute, uint8_t second) const;

	static const uint8_t INVALID_VALUE = 99;

	uint8_t m_hour = INVALID_VALUE;
	uint8_t m_minute = INVALID_VALUE;
	uint8_t m_second = INVALID_VALUE;
};
