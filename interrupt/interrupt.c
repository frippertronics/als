#include "interrupt/interrupt.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <stdbool.h>

#include "gpio/gpio.h"
#include "pwm/pwm.h"

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
volatile bool buzzer_is_active = false;
ISR(TIM0_COMPA_vect)
{
    if (PWM_IsBuzzerEnabled())
    {
        if (buzzer_is_active)
        {
            GPIO_ClearBuzzer();
        }
        else
        {
            GPIO_SetBuzzer();
        }
        buzzer_is_active = !buzzer_is_active;
    }
}

ISR(TIM0_COMPB_vect)
{

}

volatile bool buzzer_enabled = false;
ISR(WDT_vect)
{
    // General system timer.
    if (buzzer_enabled)
    {
        GPIO_ClearBuzzer();
        PWM_DisableBuzzer();
    }
    else
    {
        PWM_EnableBuzzer();
        GPIO_SetBuzzer();
    }
    buzzer_enabled = !buzzer_enabled;
}

ISR(ADC_vect)
{

}
