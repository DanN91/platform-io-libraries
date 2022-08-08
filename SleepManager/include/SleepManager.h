/*
    SleepManager: Facade wrapping ATMEGA328 deep sleep functionality and energy saving tips
    Author: Daniel Nistor
    MIT License, 2022
    Adaptated from https://www.youtube.com/watch?v=urLSDi7SD8M&t=181s
*/
#pragma once

#include "SleepManagerMasks.h"

using HandlerFunc = void(*)();

class SleepManager final
{
public:
    SleepManager(SleepMask mask, uint32_t sleepDurationSec, HandlerFunc prepareSleep = nullptr, HandlerFunc onWakeUp = nullptr);
    ~SleepManager() = default;

    void Initialize();

    void Sleep() const;

    // non-copyable & non-movable
    SleepManager(const SleepManager&) = delete;
    SleepManager& operator=(const SleepManager&) = delete;
    SleepManager(SleepManager&&) = delete;
    SleepManager& operator=(SleepManager&&) = delete;

private:
    const SleepMask m_optionsMask = SleepMask::None;
    const uint32_t m_sleepCounter = 0;
    const uint8_t m_interruptPin = 0;
    const HandlerFunc m_prepare = nullptr;
    const HandlerFunc m_onWakeUp = nullptr;
};
