/*
    SleepManager: Facade wrapping ATMEGA328 deep sleep functionality and energy saving tips
    Author: Daniel Nistor
    MIT License, 2022
    Adaptated from https://www.youtube.com/watch?v=urLSDi7SD8M&t=181s
*/

#include <Arduino.h>
#include "SleepManager.h"

SleepManager::SleepManager(SleepMask mask, uint32_t sleepDurationSec, HandlerFunc beforeSleep, HandlerFunc onWakeUp = nullptr)
    : m_optionsMask(mask)
    , m_sleepCounter(sleepDurationSec / 8) // prescaller yields every 8 seconds
    , m_prepare(beforeSleep)
    , m_onWakeUp(onWakeUp)
    , m_interruptPin(
        !!(m_optionsMask & SleepMask::UseInterrupt0) ? digitalPinToInterrupt(2)
        : !!(m_optionsMask & SleepMask::UseInterrupt1) ? digitalPinToInterrupt(3)
            : 0)
{
}

void SleepManager::Initialize()
{
    if (!!(m_optionsMask & SleepMask::DisableADC))
        ADCSRA &= ~(1 << ADEN); // Disable ADC
    
    if (!!(m_optionsMask & SleepMask::AllUnusedPinsLow))
    {
        // set all DIGITAL IO pins as output so that they will be set to LOW
        for (uint8_t i = 0; i < 20; ++i)
            pinMode(i, OUTPUT);
    }

    // Setup WatchDog Timer
    WDTCSR = (1 << WDCE) | (1 << WDE); // change enable and WDE - also resets ( WDCE + WDE set to 1 )
    WDTCSR = (1 << WDP3) | (1 << WDP0); // prescalers only - clear the WDE and WDCE bit
    WDTCSR |= (1 << WDIE); // enable interrupt mode

    // Sleep Setup
    SMCR |= (1 << SM1); // Power Down Mode
    SMCR |= (1 << SE); // Enable sleep ( step #4 must be called to go to sleep )
}

void SleepManager::Sleep() const
{
    for (uint32_t i = 0; i < m_sleepCounter; ++i) // gives double the time = 16 sec
    {
        // setup external interrupt
        if (!!(m_optionsMask & SleepMask::UseInterrupt0) || !!(m_optionsMask & SleepMask::UseInterrupt1))
            attachInterrupt(m_interruptPin, [](){}, FALLING);

        // do user-defined things before going to sleep
        if (m_prepare)
            m_prepare();

        if (!!(m_optionsMask & SleepMask::DisableBOD))
        {
            // Turn off BOD while Sleeping: This must be set after sleep is enabled and before sleep is called
            MCUCR |= (1 << BODS) | (1 << BODSE); // both BODS and BODSE at the same time
            MCUCR = (MCUCR & ~(1 << BODSE)) | (1 << BODS); // clear BODSE bit and set BODS bit at the same time
        }

        __asm__ __volatile__("sleep");

        // do user-defined things after waking up
        if (m_onWakeUp)
        {
            if (!!(m_optionsMask & SleepMask::UseInterrupt0) || !!(m_optionsMask & SleepMask::UseInterrupt1))
                detachInterrupt(m_interruptPin);
            m_onWakeUp();
        }
    }
}

// Watchdog interrupt routine
ISR(WDT_vect)
{
    Serial.println("Woke up.");
}
