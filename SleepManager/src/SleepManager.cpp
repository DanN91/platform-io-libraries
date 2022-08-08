/*
    SleepManager: Facade wrapping ATMEGA328 deep sleep functionality and energy saving tips
    Author: Daniel Nistor
    MIT License, 2022
    Adaptated from https://www.youtube.com/watch?v=urLSDi7SD8M&t=181s
*/

#include <Arduino.h>
#include "SleepManager.h"

SleepManager::SleepManager(SleepMask mask, uint32_t sleepDurationSec)
    : m_optionsMask(mask)
    , m_sleepCounter(sleepDurationSec / 8) // prescaller yields every 8 seconds
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
        if (!!(m_optionsMask & SleepMask::UseInterrupt0))
            attachInterrupt(0, [](){}, FALLING);

        if (!!(m_optionsMask & SleepMask::UseInterrupt1))
            attachInterrupt(1, [](){}, FALLING);

        if (!!(m_optionsMask & SleepMask::DisableBOD))
        {
            // Turn off BOD while Sleeping: This must be set after sleep is enabled and before sleep is called
            MCUCR |= (1 << BODS) | (1 << BODSE); // both BODS and BODSE at the same time
            MCUCR = (MCUCR & ~(1 << BODSE)) | (1 << BODS); // clear BODSE bit and set BODS bit at the same time
        }

        __asm__ __volatile__("sleep");
    }
}

/*
    Kevin's Darrah code

    #define LED_PIN 4
void setup() {
  pinMode(LED_PIN, OUTPUT);
  
  
  //Save Power by writing all Digital IO LOW - note that pins just need to be tied one way or another, do not damage devices!
  for (int i = 0; i < 20; i++) {
    if(i != 2)//just because the button is hooked up to digital pin 2
    pinMode(i, OUTPUT);
  }
  
  attachInterrupt(0, digitalInterrupt, FALLING); //interrupt for waking up
  
  
  //SETUP WATCHDOG TIMER
WDTCSR = (24);//change enable and WDE - also resets
WDTCSR = (33);//prescalers only - get rid of the WDE and WDCE bit
WDTCSR |= (1<<6);//enable interrupt mode

  //Disable ADC - don't forget to flip back after waking up if using ADC in your application ADCSRA |= (1 << 7);
  ADCSRA &= ~(1 << 7);
  
  //ENABLE SLEEP - this enables the sleep mode
  SMCR |= (1 << 2); //power down mode
  SMCR |= 1;//enable sleep
}

void loop() {

  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);

  //BOD DISABLE - this must be called right before the __asm__ sleep instruction
  MCUCR |= (3 << 5); //set both BODS and BODSE at the same time
  MCUCR = (MCUCR & ~(1 << 5)) | (1 << 6); //then set the BODS bit and clear the BODSE bit at the same time
  __asm__  __volatile__("sleep");//in line assembler to go to sleep

}

void digitalInterrupt(){
  //needed for the digital input interrupt
}

ISR(WDT_vect){
  //DON'T FORGET THIS!  Needed for the watch dog timer.  This is called after a watch dog timer timeout - this is the interrupt function called after waking up
}// watchdog interrupt

*/