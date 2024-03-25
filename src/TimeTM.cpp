/*
 *	TimeTM - Library for storing time in 24h format.
*/

#include "TimeTM.h"

namespace
{
	constexpr uint8_t MIN_HOUR_MINUTE = 0;
	constexpr uint8_t MAX_HOUR = 23;
	constexpr uint8_t MAX_MINUTE = 59;

	const char* TIME_SEPARATOR = ":";
} // anonymous

TimeTM::TimeTM(uint8_t hour, uint8_t minute, uint8_t second)
{
	if (!IsTimeValid(hour, minute, second))
		return;

	SetTime(hour, minute, second);
}

bool TimeTM::SetHour24(uint8_t hour)
{
	// 24hFormat
	if ((hour >= MIN_HOUR_MINUTE) && (hour <= MAX_HOUR))
	{
		m_hour = hour;
		return true;
	}
	
	return false;
}

bool TimeTM::SetMinute(uint8_t minute)
{
	if ((minute >= MIN_HOUR_MINUTE) && (minute <= MAX_MINUTE))
	{
		m_minute = minute;
		return true;
	}

	return false;
}

bool TimeTM::SetSecond(uint8_t second)
{
	if ((second >= MIN_HOUR_MINUTE) && (second <= MAX_MINUTE))
	{
		m_second = second;
		return true;
	}

	return false;
}

bool TimeTM::SetTime(uint8_t hour, uint8_t minute, uint8_t second)
{
	if (!IsTimeValid(hour, minute, second))
		return false;

	m_hour = hour;
	m_minute = minute;
	m_second = second;

	return true;
}

uint8_t TimeTM::GetHour24() const
{
	return m_hour;
}

uint8_t TimeTM::GetMinute() const
{
	return m_minute;
}

uint8_t TimeTM::GetSecond() const
{
	return m_second;
}

String TimeTM::GetTimeFormatted() const
{
	if (!(*this))
		return "Invalid time";

	// <HH:MM:SS>
	String time;

	if (m_hour < 10)
		time += "0";

	time += m_hour;

	time += TIME_SEPARATOR;

	if (m_minute < 10)
		time += "0";

	time += m_minute;

	time += TIME_SEPARATOR;

	if (m_second < 10)
		time += "0";

	time += m_second;

	return time;
}

bool operator == (const TimeTM& lhs, const TimeTM& rhs)
{
	return lhs && rhs && lhs.GetHour24() == rhs.GetHour24() && lhs.GetMinute() == rhs.GetMinute() && lhs.GetSecond() == rhs.GetSecond();
}

bool operator >= (const TimeTM& lhs, const TimeTM& rhs)
{
	return lhs && rhs
		&& lhs.GetHour24() >= rhs.GetHour24()
		&& lhs.GetMinute() >= rhs.GetMinute()
		&& lhs.GetSecond() >= rhs.GetSecond();
}

TimeTM::operator bool() const
{
	return IsTimeValid(m_hour, m_minute, m_second);
}

bool TimeTM::IsTimeValid(uint8_t hour, uint8_t minute, uint8_t second) const
{
	return ((hour >= MIN_HOUR_MINUTE && hour <= MAX_HOUR)
	&& (minute >= MIN_HOUR_MINUTE && minute <= MAX_MINUTE)
	&& (second >= MIN_HOUR_MINUTE && second <= MAX_MINUTE));
}