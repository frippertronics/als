#include "gpio/gpio.h" 

#include <avr/io.h>

static void GPIO_SetPin(volatile uint8_t* pPort, uint8_t pin);
static void GPIO_ClearPin(volatile uint8_t* pPort, uint8_t pin);
typedef enum 
{
    INPUT = 0,
    OUTPUT = 1
} GPIO_DIR_E;

static void GPIO_InitPin(volatile uint8_t* pDdr, uint8_t pin, GPIO_DIR_E direction)
{
    if (direction == OUTPUT)
    {
        *pDdr |= (1 << pin);
    }
    else
    {
        *pDdr &= ~(1 << pin);
    }
}

static void GPIO_SetPin(volatile uint8_t* pPort, uint8_t pin)
{
    *pPort |= (1 << pin);
}

static void GPIO_ClearPin(volatile uint8_t* pPort, uint8_t pin)
{
    *pPort &= ~(1 << pin);
}

void GPIO_Setup(void)
{
    GPIO_InitPin(&DDRB, DDB4, OUTPUT); // Was PORTB which caused low output voltage
}

void GPIO_SetBuzzer(void)
{
    GPIO_SetPin(&PORTB, PB4);
}

void GPIO_ClearBuzzer(void)
{
    GPIO_ClearPin(&PORTB, PB4);
}
