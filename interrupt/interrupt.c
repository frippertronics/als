#include "interrupt/interrupt.h"

#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

volatile bool g_watchdog_interrupt = false;
volatile bool g_adc_interrupt = false;
volatile bool g_pwm_interrupt = false;

void INT_Disable(void)
{
    SREG = (0 << 7);
}

void INT_Enable(void)
{
    SREG = (1 << 7);
}

void INT_Setup(void)
{
    INT_Enable();
}

ISR(INT0_vect)
{
}

ISR(PCINT0_vect)
{
}

ISR(TIM0_OVF_vect)
{
}

ISR(EE_RDY_vect)
{
}

ISR(ANA_COMP_vect)
{
}

// PWM
ISR(TIM0_COMPA_vect)
{
    g_pwm_interrupt = true;
}

ISR(TIM0_COMPB_vect)
{
}

ISR(WDT_vect)
{
    g_watchdog_interrupt = true;
}

ISR(ADC_vect)
{
    g_adc_interrupt = true;  
}
