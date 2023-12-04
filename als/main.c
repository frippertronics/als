#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>

#include <avr/io.h>
#include <avr/sleep.h>

#include "adc/adc.h"
#include "gpio/gpio.h"
#include "interrupt/interrupt.h"
#include "pwm/pwm.h"
#include "sleep/sleep.h"

#define MAX_SLEEP_TIME (300)
#define SECONDS_TO_BUZZ (1)

typedef enum
{
    STATE_IDLE = 0,
    STATE_BUZZ = 1,
    STATE_GET_RAND = 2,
} fsm_states_e;

static void WDT_Setup(void)
{
    // Enable change-mode on the WDT, disable watchdog reset
    WDTCR |= (1 << WDCE) | (0 << WDE);
    // WDT clock is independent of system clock, so scale to 1 second
    WDTCR |= (1 << WDTIE) | (0 << WDP3) | (1 << WDP2) | (1 << WDP1) | (0 << WDP0);
}

static void rand_init(uint16_t seed)
{
    srand(seed);
}

static uint16_t rand_get(void)
{
    return (rand() % (MAX_SLEEP_TIME + 1));
}

int main(void)
{
    fsm_states_e state = STATE_GET_RAND;
    uint16_t watchdog_count = 0;
    uint16_t watchdog_count_to_trigger = 0;
    uint16_t buzzer_cycles = 0;
    bool buzzer_toggle = false;
    
    // Modules
    GPIO_Setup();
    PWM_Setup();
    Sleep_Setup();
    ADC_Setup();
    WDT_Setup();

    // Enable interrupts last to avoid funky behaviour
    INT_Setup();
    
    for(;;)
    {
        if (state == STATE_IDLE)
        {
            if (g_watchdog_interrupt)
            {
                watchdog_count++;

                if (watchdog_count > watchdog_count_to_trigger)
                {
                    // The clock for the buzzer PWM runs only when the device is
                    // sleeping in IDLE mode.
                    Sleep_SetMode(IDLE);
                    buzzer_toggle = true;
                    watchdog_count = 0;
                    state = STATE_BUZZ;
                }
                g_watchdog_interrupt = false;
            }
        }
        else if (state == STATE_BUZZ)
        {
            if (g_pwm_interrupt)
            {
                if (buzzer_toggle)
                {
                    GPIO_SetBuzzer();
                }
                else
                {
                    GPIO_ClearBuzzer();
                }
                buzzer_toggle = !buzzer_toggle;
                buzzer_cycles++;
                
                // Buzzer runs at ~4 kHz
                if (buzzer_cycles > (SECONDS_TO_BUZZ * 4000))
                {
                    GPIO_ClearBuzzer();
                    // POWER_DOWN stops the PWM clock from running
                    Sleep_SetMode(POWER_DOWN);
                    buzzer_cycles = 0;
                    watchdog_count_to_trigger = rand_get();
                    state = STATE_IDLE;
                }
                g_pwm_interrupt = false;
            }
        }
        else if (state == STATE_GET_RAND)
        {
            if (g_adc_interrupt == false)
            {
                ADC_StartMeasurement();
            }
            else
            {
                rand_init(ADC_GetMeasurement());
                ADC_StopMeasurement();
                watchdog_count_to_trigger = rand_get();
                Sleep_SetMode(POWER_DOWN);
                state = STATE_IDLE;
                g_adc_interrupt = false;
            }
        }
        else
        {
            state = STATE_IDLE;
        }
        
        // Stay awake when performing ADC conversion to get as much noise as possible
        if (state != STATE_GET_RAND)
        {
            Sleep_Enter();
        }
    }
}