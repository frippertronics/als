cmake_minimum_required(VERSION 3.20)

# Use AVR GCC toolchain, set this first to force CMake to use it.
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_ASM_COMPILER avr-gcc)

project("als"
    VERSION 1.0
    LANGUAGES C
)

# Group all AVR-related argumnts into a board-library as all other
# "libraries" interface directly with the avr-gcc libraries
add_library(board INTERFACE)
# CPU, from here:
# https://gcc.gnu.org/onlinedocs/gcc/AVR-Options.html
set(MCU attiny13)

# AVR Fuses, must be in concordance with hardware and F_CPU
# http://eleccelerator.com/fusecalc/fusecalc.php?chip=atmega2560
set(E_FUSE 0xFF)
set(H_FUSE 0xFF)
set(L_FUSE 0x7A) # Clock divided by 9.6 -> 1.2 MHz main clock frequency
set(LOCK_BIT 0xFF)

target_compile_definitions(board INTERFACE
    F_CPU=9600000UL # Clock rate, used for delay_ms etc.
)

target_compile_options(board INTERFACE
    -mmcu=${MCU}
    -std=gnu99
    -Os
    -Wall
    -Wundef
    -pedantic
    -Wstrict-prototypes
    -Werror
    -Wfatal-errors
    -Wl,--relax,--gc-sections
    -funsigned-char
    -funsigned-bitfields
    -fpack-struct
    -fshort-enums
    -ffunction-sections
    -fdata-sections
    -fno-split-wide-types
    -fno-tree-scev-cprop
)

# mmcu MUST be passed to both the compiler and linker
target_link_options(board INTERFACE
    -mmcu=${MCU}
)

# Libraries
add_subdirectory(adc)
add_subdirectory(gpio)
add_subdirectory(interrupt)
add_subdirectory(pwm)
add_subdirectory(sleep)

# Executable
add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} adc board gpio interrupt pwm sleep)

# Strip binary for upload
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}.elf)
add_custom_target(strip ALL avr-strip ${PROJECT_NAME}.elf DEPENDS ${PROJECT_NAME})

# Transform binary into hex file, we ignore the eeprom segments in the step
add_custom_target(hex ALL avr-objcopy -R .eeprom -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex DEPENDS strip)

# Clean extra files
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${PROJECT_NAME}")
