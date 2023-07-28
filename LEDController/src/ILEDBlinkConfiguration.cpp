/*
    ILEDBlinkConfiguration: Interface for non-blocking blinking of one or multiple LED(s) using Composite pattern.
    Author: Daniel Nistor
    MIT License, 2023
*/
#pragma once

#include "ILEDBlinkConfiguration.h"

ILEDBlinkConfiguration::ILEDBlinkConfiguration(uint32_t intervalMs)
    : m_intervalMs(intervalMs)
{
}

ILEDBlinkConfiguration::ILEDBlinkConfiguration(uint32_t intervalMs, uint8_t times)
    : m_intervalMs(intervalMs), m_times(times)
{
}
