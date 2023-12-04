#pragma once

#include <stdint.h>

extern void ADC_Setup(void);
extern void ADC_StartMeasurement(void);
extern void ADC_StopMeasurement(void);
extern uint16_t ADC_GetMeasurement(void);
