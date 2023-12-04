#include <avr/io.h>

void ADC_Setup(void)
{
    ADMUX = (1 << MUX1) | (1 << MUX0); // PB3
    ADCSRA = (0 << ADEN) | (1 << ADIE); // Enable interrupt
    ADCSRB = (0 << ADTS2) | (0 << ADTS1) | (0 << ADTS0); // Free-running
}

void ADC_StartMeasurement(void)
{
    ADCSRA |= (1 << ADEN) | (1 << ADSC);
}

void ADC_StopMeasurement(void)
{
    ADCSRA &= ~((1 << ADEN) | (1 << ADSC));
}

uint16_t ADC_GetMeasurement(void)
{
    uint16_t adc_val = ADCH;
    adc_val |= (adc_val << 8) | (ADCL);
    return adc_val;
}
