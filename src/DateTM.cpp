/*
 *	DateTM - Library for storing date.
 */

#include "DateTM.h"

namespace
{
	constexpr uint8_t MIN_DAY = 1;
	constexpr uint8_t MAX_DAY = 31;

	constexpr uint8_t MAX_MONTH = 12;

	constexpr uint16_t BASE_YEAR = 2000;

	constexpr uint16_t MIN_YEAR = 2000;
	constexpr uint16_t MAX_YEAR = 2255; // BASE_YEAR + max value of uint8_t 255 [0, 255]

	const char DATE_SEPARATOR = '/';
} // anonymous

DateTM::DateTM(uint8_t day, uint8_t month, uint8_t year)
{
	if (!IsDateValid(day, month, year))
		return;

	SetDate(day, month, year);
}

bool DateTM::SetDay(uint8_t day)
{
	if (!IsDateValid(day, m_month, m_year))
		return false;

	m_day = day;
	return true;
}

bool DateTM::SetMonth(uint8_t month)
{
	if (!IsDateValid(m_day, month, m_year))
		return false;

	m_month = static_cast<Month>(month);
	return true;
}

bool DateTM::SetYear(uint8_t year)
{
	if (!IsDateValid(m_day, m_month, year))
		return false;

	m_year = year;
	return true;
}

bool DateTM::SetDate(uint8_t day, uint8_t month, uint8_t year)
{
	if (!IsDateValid(day, month, year))
		return false;

	m_day = day;
	m_month = static_cast<Month>(month);
	m_year = year;

	return true;
}

uint8_t DateTM::GetDay() const
{
	return m_day;
}

uint8_t DateTM::GetMonth() const
{
	return m_month;
}

uint16_t DateTM::GetYear(bool useShortVersion) const
{
	return m_year + (useShortVersion ? 0 : BASE_YEAR);
}

bool DateTM::AddDays(uint8_t days)
{
	auto day = m_day;
	auto month = m_month;
	auto year = m_year;

	while (days > 0)
	{
		const auto maxMonthDay = GetValidMaxDay(month, BASE_YEAR + year);
		const auto daysLeftInMonth = maxMonthDay - day;

		if (days > daysLeftInMonth) // month overflow
		{
			month = static_cast<Month>((month == Month::December) ? Month::January : month + 1);
			if (month == 1)
			{
				year += 1;
			}

			day = (day + daysLeftInMonth) % maxMonthDay;
			days -= daysLeftInMonth;
		}
		else
		{
			day += days;
			break;
		}
	}

	return SetDate(day, month, year);
}

String DateTM::GetDateFormatted() const
{
	if (!(*this))
		return "Invalid date";

	// <DD/MM/YYYY>
	String date;

	if (m_day < 10)
		date += "0";

	date += m_day;

	date += DATE_SEPARATOR;

	if (m_month < Month::October)
		date += "0";

	date += static_cast<uint8_t>(m_month);

	date += DATE_SEPARATOR;

	date += GetYear();

	return date;
}

bool operator == (const DateTM& lhs, const DateTM& rhs)
{
	return lhs && rhs
		&& lhs.GetDay() == rhs.GetDay()
		&& lhs.GetMonth() == rhs.GetMonth()
		&& lhs.GetYear() == rhs.GetYear();
}

bool operator >= (const DateTM& lhs, const DateTM& rhs)
{
	return lhs && rhs
		&& lhs.GetDay() >= rhs.GetDay()
		&& lhs.GetMonth() >= rhs.GetMonth()
		&& lhs.GetYear() >= rhs.GetYear();
}

DateTM::operator bool() const
{
	return IsDateValid(m_day, m_month, m_year);
}

uint8_t DateTM::GetValidMaxDay(Month month, uint16_t year) const
{
	// february, determine number of days by whether is common or leap year
	if (month == Month::February)
	{
		return IsLeapYear(year) ? 29 : 28;
	}

	switch (month)
	{
		case Month::April:
		case Month::June:
		case Month::September:
		case Month::November:
			return 30;
		default:
			return MAX_DAY;
	}
}

bool DateTM::IsLeapYear(uint16_t year) const
{
	return ((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0)));
}

bool DateTM::IsDateValid(uint8_t day, uint8_t month, uint8_t year) const
{
	const uint16_t fullYear = BASE_YEAR + year;

	if (day < MIN_DAY || day > GetValidMaxDay(static_cast<Month>(month), fullYear))
		return false;

	if (month < Month::January || month > Month::December)
		return false;

	if (fullYear < MIN_YEAR || fullYear > MAX_YEAR)
		return false;

	return true;
}