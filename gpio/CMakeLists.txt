set(LIBRARY_FILENAME gpio)

add_library(${LIBRARY_FILENAME} gpio.c)
target_include_directories(${LIBRARY_FILENAME} PUBLIC ../include)
