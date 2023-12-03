#include <stdint.h>
#include <util/delay.h>

#include <avr/io.h>
#include <avr/sleep.h>

#include "gpio/gpio.h"
#include "interrupt/interrupt.h"
#include "pwm/pwm.h"
#include "sleep/sleep.h"

static void WDT_Setup(void)
{
    WDTCR |= (1 << WDCE) | (0 << WDE);
    // System clock is independent of system clock, so scale to 1 second
    WDTCR |= (1 << WDTIE) | (0 << WDP3) | (1 << WDP2) | (1 << WDP1) | (0 << WDP0);
}

static void init(void)
{
    // Modules
    GPIO_Setup();
    PWM_Setup();
    Sleep_Setup();
    WDT_Setup();

    // Enable interrupts last to avoid funky behaviour
    INT_Setup();
}

int main(void)
{
    init();  
    //PWM_EnableBuzzer();
    for(;;)
    {
        //GPIO_SoundDebug();
        //GPIO_ToggleDebug(1);
        Sleep_Enter();
        // Sanity buzzer
        /*
        GPIO_ClearBuzzer();
        _delay_us(15);
        GPIO_SetBuzzer();
        _delay_us(15);
        */
    }
}