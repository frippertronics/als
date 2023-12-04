# Define an executable file
add_executable(${PRODUCT_NAME} main.c)

set_target_properties(${PRODUCT_NAME} PROPERTIES OUTPUT_NAME ${PRODUCT_NAME}.elf)

# Link the compiled libraries to the executable.
target_link_libraries(${PRODUCT_NAME} PRIVATE adc gpio interrupt pwm sleep)

# Strip binary for upload
add_custom_target(strip ALL avr-strip ${PRODUCT_NAME}.elf DEPENDS ${PRODUCT_NAME})

# Transform binary into hex file, we ignore the eeprom segments in the step
add_custom_target(hex ALL avr-objcopy -R .eeprom -O ihex ${PRODUCT_NAME}.elf ${PRODUCT_NAME}.hex DEPENDS strip)
