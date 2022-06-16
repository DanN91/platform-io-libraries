/*
    SleepManager: Facade wrapping ATMEGA328 deep sleep functionality and energy saving tips
    Author: Daniel Nistor
    MIT License, 2022
    Adaptated from https://www.youtube.com/watch?v=urLSDi7SD8M&t=181s
*/
#pragma once

#include "SleepManagerMasks.h"

class SleepManager final
{
public:
    SleepManager(SleepMask mask, uint32_t sleepDurationSec);
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
};

/*
#include <Arduino.h>

// Source: https://www.youtube.com/watch?v=urLSDi7SD8M
// Optimizing Power Consumption & Sleep mode
// 1. Put all unused DIGITAL IO pins to LOW state as OUTPUT
// 2. Disable ADC: ADCSRA &= ~(1 << ADEN);
// 3a. Enable PowerDown sleep mode
//     SMCR |= (1 << SM1); // Power Down Mode
//     SMCR |= (1 << SE); // Enable sleep ( step #4 must be called to go to sleep )
// 3b. Turn off BOD while Sleeping: This must be set after sleep is enabled and before sleep is called
//     MCUCR |= (1 << BODS) | (1 << BODSE); // both BODS and BODSE at the same time
//     MCUCR = (MCUCR & ~(1 << BODSE)) | (1 << BODS); // clear BODSE bit and set BODS bit at the same time
// 4. Go to sleep: __asm__ __volatile__("sleep");

// Wake Up By Watchdog Timer once every 8s (13:15), in SETUP ( 0.007 mA )
// 1. WDTCSR = (1 << WDCE) | (1 << WDE); // change enable and WDE - also resets ( WDCE + WDE set to 1 )
// 2. WDTCSR = (1 << WDP3) | (1 << WDP0); // prescalers only - clear the WDE and WDCE bit
// 3. WDTCSR |= (1 << WDIE); // enable interrupt mode
// 4. Increase the 8s to what you desire by going back to sleep until it's really time to wake up
//     -> set the BOD disable before going back to sleep
// 5. Use Watchdog ISR: ISR(WDT_vect) { <code> }
//

// constexpr const uint8_t TOTAL_DIGITAL_IO_PIN_COUNT = 20;
// const uint8_t USED_PINS[] = { 13 };

// bool isPinUsed(uint8_t pin)
// {
//     for (uint8_t i = 0; i < sizeof(USED_PINS); ++i)
//     {
//         if (pin == USED_PINS[i])
//             return true;
//     }

//     return false;
// }

void setup()
{
    Serial.begin(115200);

    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);

    // Put all unused DIGITAL IO pins to LOW state as OUTPUT
    // for (uint8_t i = 0; i < TOTAL_DIGITAL_IO_PIN_COUNT; ++i)
    // {
    //     if (!isPinUsed(i))
    //         pinMode(i, OUTPUT);
    // }

    // Setup WatchDog Timer
    WDTCSR = (1 << WDCE) | (1 << WDE); // change enable and WDE - also resets ( WDCE + WDE set to 1 )
    WDTCSR = (1 << WDP3) | (1 << WDP0); // prescalers only - clear the WDE and WDCE bit
    WDTCSR |= (1 << WDIE); // enable interrupt mode

    // Disable ADC
    ADCSRA &= ~(1 << ADEN);

    // Sleep Setup
    SMCR |= (1 << SM1); // Power Down Mode
    SMCR |= (1 << SE); // Enable sleep ( step #4 must be called to go to sleep )

    // Turn off BOD while Sleeping: This must be set after sleep is enabled and before sleep is called
    MCUCR |= (1 << BODS) | (1 << BODSE); // both BODS and BODSE at the same time
    MCUCR = (MCUCR & ~(1 << BODSE)) | (1 << BODS); // clear BODSE bit and set BODS bit at the same time
}

// Watchdog interrupt routine
ISR(WDT_vect)
{
    // Serial.println("Woke up.");
}

void loop()
{
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);

    __asm__ __volatile__("sleep");
}
*/