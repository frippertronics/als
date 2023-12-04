#include "pwm/pwm.h" 

#include <avr/io.h>

// The I/O CLK is 9.6 MHz by default but scaled to 1/8 = 1.2 MHz
// With a prescaler of 8, the resulting frequency is 150 KHz
// To get a 4 KHz output, we need a period of 0.25 ms.
// 1 PWM tick equals 6.67 us, so that gives:
// 17 = 4409 Hz
// 18 = 4164 Hz 
// 19 = 3968 Hz
#define BUZZ_PWM_COMPARE_VAL (17)

static volatile bool s_buzzer_is_enabled = false;

void PWM_EnableBuzzer(void)
{
    s_buzzer_is_enabled = true;
}

void PWM_DisableBuzzer(void)
{
    s_buzzer_is_enabled = false;
}

bool PWM_IsBuzzerEnabled(void)
{
    return s_buzzer_is_enabled;
}

void PWM_Setup(void)
{
    // Set to CTC mode to trigger an interrupt every 
    TCCR0A = (1 << WGM01) | (0 << WGM00); // CTC mode
    TCCR0B = (0 << WGM02) | (0 << CS02) | (1 << CS01) | (0 << CS00); // Prescale clock to clkIO / 8
    
    TCNT0 = 0;
    OCR0A = BUZZ_PWM_COMPARE_VAL;

    // Enable interrupts for PWM
    TIMSK0 = (0 << OCIE0B) | (1 << OCIE0A) | (0 << TOIE0);
}
