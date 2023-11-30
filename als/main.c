#include "gpio/gpio.h"
#include "interrupt/interrupt.h"

#include <stdint.h>
#include <util/delay.h>

static void init(void)
{
    // Modules
    GPIO_Setup();

    // Enable interrupts last to avoid funky behaviour
    INT_Setup();
}

int main(void)
{
    init();
    
    while(1)
    {
        // Sanity buzzer
        GPIO_ClearBuzzer();
        _delay_us(15);
        GPIO_SetBuzzer();
        _delay_us(15);
    }
}