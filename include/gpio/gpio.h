#pragma once

#include <stdint.h>

extern void GPIO_Setup(void);
extern void GPIO_SetBuzzer(void);
extern void GPIO_ClearBuzzer(void);
extern void GPIO_ToggleDebug(uint8_t num);
extern void GPIO_SoundDebug(void);
