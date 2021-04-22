/*
    RangeValuesGenerator: increments value in a set range by whenever the observed push button is released.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "RangeValuesGenerator.h"

#include <PushButton.h>

RangeValuesGenerator::RangeValuesGenerator(uint16_t min, uint16_t max, uint8_t step, IObservable<ButtonState>& button)
    : IObserver<ButtonState>(ButtonState::Released, button)
    , m_step(step)
{
    Range(min, max);
}

void RangeValuesGenerator::OnEvent(ButtonState event)
{
    if (m_isRangeValid && event == ButtonState::Released)
    {
        const auto nextValue = m_current + m_step;
        m_current = (nextValue > m_maximum) ? m_minimum : nextValue;
    }
}

uint16_t RangeValuesGenerator::Value() const
{
    return m_current;
}

bool RangeValuesGenerator::Range(uint16_t min, uint16_t max)
{
    if (min >= max)
    {
        m_isRangeValid = false;
        return m_isRangeValid; // exceeds data type or invalid
    }

    m_minimum = min;
    m_maximum = max;
    m_current = m_minimum; // start from min
    m_isRangeValid = true;

    return true;
}

RangeValuesGenerator::ValuesRange RangeValuesGenerator::Range() const
{
    return { m_minimum, m_maximum };
}

bool RangeValuesGenerator::IsValid() const
{
    return m_isRangeValid;
}