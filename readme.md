# Annoying Little Shit

The Annoying Little Shit (ALS) is a piece of annoying kit that
wakes up at a random point of time and buzzes loudly.
It has a life of its own and should be small enough to be placed
in hard-to-find places.

## Details

The device uses the AVR's watchdog timer as a periodic interrupt
to wake up from power-down mode. This happens at an interval of 8 seconds. After waking up for a random number of times,
the device makes a loud beeping noise before going back to
sleep again for a new random number of wakeups.

The minimum sleep time is 60 minutes, and the longest is 26.6 hours.

## Power Consumption

In sleep, or "power down" mode, the device consumes between 5 or 10 uA,
and when buzzing it consumes roughly 110 mA. Each buzz consumes
110 mA * 1 second = 110 mAs = 0.03 mAh, while 1 hour of sleep consumes 10 uA * 3600 = 0.036 mAh.
The CR2032 battery has a capacity of 240 mAh.
Assuming an average of 2 buzzes per day,
this roughly results in a daily energy consumption of
24 * 0.036 mAh + 2 * 0.030 mAh = 0.924 mAh/day, or
a lifetime of 260 days.

## Firmware

The firmware is written for the AVR ATTiny13. The design files for
the device can be found [here](https://github.com/frippertronics/als-hardware)!

The firmware uses the following AVR features:

- ADC, to generate a random number based on a floating pin.
- Interrupts, to get regularly timed events and to get the ADC value.
- PWM, to get a regular interval to cycle the buzzer output.
- WDT, as a general system timer to save energy between buzzes.
- GPIO, to trigger the buzzer.

Requirements:

- CMake
- avr-gcc
