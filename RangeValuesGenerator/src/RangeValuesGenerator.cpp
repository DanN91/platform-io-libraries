/*
    RangeValuesGenerator: increments value in a set range by whenever the observed push button is released.
    Author: Daniel Nistor
    MIT License, 2021
*/

#include "RangeValuesGenerator.h"

#include <PushButton.h>

RangeValuesGenerator::RangeValuesGenerator(ValuesRange range, uint32_t step, uint32_t start, IObservable<ButtonState>& button, ButtonState event)
    : IObserver<ButtonState>(event, button)
    , m_range(range)
    , m_step(step)
    , m_current(m_range.IsInRange(start) ? start : m_range.Min())
{
}

void RangeValuesGenerator::OnEvent(ButtonState event)
{
    if (m_range && event == Events())
    {
        const auto nextValue = m_current + m_step;
        m_current = (nextValue > m_range.Max()) ? m_range.Min() : nextValue;
    }
}

uint32_t RangeValuesGenerator::Value() const
{
    return m_current;
}

void RangeValuesGenerator::Range(ValuesRange range)
{
    m_range = range;
    m_current = m_range.Min(); // start from min
}

ValuesRange RangeValuesGenerator::Range() const
{
    return m_range;
}

bool RangeValuesGenerator::IsValid() const
{
    return m_range ? true : false;
}