#include "interrupt/interrupt.h" 

#include <avr/io.h>
#include <avr/interrupt.h>


void INT_Setup(void)
{
    sei();
}

// Timer
ISR(TIM0_OVF_vect)
{
    //
}
