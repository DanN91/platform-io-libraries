#include <Arduino.h>
#include <SleepManager.h>

/*
    Source: https://www.youtube.com/watch?v=urLSDi7SD8M
    Optimizing Power Consumption & Sleep mode
    1. Put all unused DIGITAL IO pins to LOW state as OUTPUT
    2. Disable ADC: ADCSRA &= ~(1 << ADEN);
    3a. Enable PowerDown sleep mode
        SMCR |= (1 << SM1); // Power Down Mode
        SMCR |= (1 << SE); // Enable sleep ( step #4 must be called to go to sleep )
    3b. Turn off BOD while Sleeping: This must be set after sleep is enabled and before sleep is called
        MCUCR |= (1 << BODS) | (1 << BODSE); // both BODS and BODSE at the same time
        MCUCR = (MCUCR & ~(1 << BODSE)) | (1 << BODS); // clear BODSE bit and set BODS bit at the same time
    4. Go to sleep: __asm__ __volatile__("sleep");
    
    Wake Up By Button via Ext Interrupt
    1. use attachInterrupt(PIN, <void:ISR>, FALLING/RISING);
    2. wire properly

    Wake Up By Watchdog Timer once every 8s (13:15), in SETUP ( 0.007 mA )
    1. WDTCSR = (1 << WDCE) | (1 << WDE); // change enable and WDE - also resets ( WDCE + WDE set to 1 )
    2. WDTCSR = (1 << WDP3) | (1 << WDP0); // prescalers only - clear the WDE and WDCE bit
    3. WDTCSR |= (1 << WDIE); // enable interrupt mode
    4. Increase the 8s to what you desire by going back to sleep until it's really time to wake up
        -> set the BOD disable before going back to sleep
    5. Use Watchdog ISR: ISR(WDT_vect) { <code> }
*/

SleepManager sleepManager(SleepMask::AllUnusedPinsLow | SleepMask::DisableADC | SleepMask::DisableBOD | SleepMask::UseInterrupt1, 16);

void setup()
{
    Serial.begin(115200);
    sleepManager.Initialize();

    pinMode(13, OUTPUT);
}

void loop()
{
    digitalWrite(13, HIGH);
    delay(2000);
    digitalWrite(13, LOW);

    sleepManager.Sleep();
}

// Watchdog interrupt routine
ISR(WDT_vect)
{
    Serial.println("Woke up.");
}