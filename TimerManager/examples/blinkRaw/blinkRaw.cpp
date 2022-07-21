#include <Arduino.h>

// Source: https://www.youtube.com/watch?v=IdL0_ZJ7V2s
bool LED_STATE = false;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    // Timer 1 has two bytes, we set the value to 0
    TCCR1A = 0;
    TCCR1B = 0;

    // compare match values
    OCR1A = 15624; // once every second

    TCCR1B &= ~(1 << WGM13); // make sure it's cleared
    TCCR1B |= (1 << CS12) | (1 << CS10) | (1 << WGM12); // Prescaller: 1024, CTC
    TIMSK1 |= (1 << OCIE1A); // Enable interrupt on OCR1A match

    sei(); // enable global interrupts
    // cli(); // disable global interrupts
}

/*
    fClock = 16 MHz ~= 1 second
    Compare value formula: OCR1A = ( fClock/(prescaler * fTarget )) - 1
        1 second:   (16*10^6 / 256)     - 1 => 62500
        1 second: (16*10^6 / 1024) - 1 => 15624
*/

// ISR called when compare A reg match happens
ISR(TIMER1_COMPA_vect)
{
    LED_STATE = !LED_STATE;
    digitalWrite(LED_BUILTIN, LED_STATE);

    Serial.print(millis());
    Serial.print(" | LED: ");
    Serial.println(LED_STATE ? "ON" : "OFF");
}

void loop()
{
    // put your main code here, to run repeatedly:
}