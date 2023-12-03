#pragma once

#include <stdbool.h>

extern void PWM_Setup(void);
extern void PWM_EnableBuzzer(void);
extern void PWM_DisableBuzzer(void);
extern bool PWM_IsBuzzerEnabled(void);
