set(LIBRARY_FILENAME pwm)

add_library(${LIBRARY_FILENAME} OBJECT pwm.c)
target_include_directories(${LIBRARY_FILENAME} PUBLIC ../include)
