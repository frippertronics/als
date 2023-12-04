#pragma once

#include <stdbool.h>

extern volatile bool g_watchdog_interrupt;
extern volatile bool g_adc_interrupt;
extern volatile bool g_pwm_interrupt;

extern void INT_Setup(void);
extern void INT_Disable(void);
extern void INT_Enable(void);
