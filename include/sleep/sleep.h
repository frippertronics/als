#pragma once

typedef enum 
{
    IDLE = 0,
    ADC_NR = 1,
    POWER_DOWN = 2
} sleep_modes_e;

extern void Sleep_Setup(void);
extern void Sleep_Enter(void);
extern void Sleep_SetMode(sleep_modes_e mode);
