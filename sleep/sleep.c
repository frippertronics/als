#include "sleep/sleep.h"

#include <avr/io.h>
#include <avr/sleep.h>
#include <stdbool.h>

#include "interrupt/interrupt.h"

void Sleep_Enter(void)
{
    sleep_mode();
}

void Sleep_SetMode(sleep_modes_e mode)
{
    INT_Disable();
    set_sleep_mode(mode);
    INT_Enable();
}

void Sleep_Setup(void)
{
    Sleep_SetMode(IDLE);
}