/*
    RangeValuesGenerator: increments value in a set range by whenever the observed push button is released.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "RangeValuesGenerator.h"

#include <PushButton.h>

RangeValuesGenerator::RangeValuesGenerator(uint8_t min, uint8_t max, IObservable<ButtonState>& button)
    : IObserver<ButtonState>(ButtonState::Released, button)
    , m_minimum(min)
    , m_maximum(max)
    , m_current(min)
{
}

void RangeValuesGenerator::OnEvent(ButtonState event)
{
    if (event == ButtonState::Released)
    {
        const uint8_t nextValue = m_current + 1;
        m_current = ((nextValue % (m_maximum + 1) == 0)) ? m_minimum : nextValue;
    }
}

uint8_t RangeValuesGenerator::Value() const
{
    return m_current;
}

bool RangeValuesGenerator::Range(uint8_t min, uint8_t max)
{
    if (min < 0 || max > 255 || (min > max))
        return false; // exceeds data type or invalid

    m_minimum = min;
    m_maximum = max;
    m_current = m_minimum; // start from min
}

RangeValuesGenerator::ValuesRange RangeValuesGenerator::Range() const
{
    return { m_minimum, m_maximum };
}
