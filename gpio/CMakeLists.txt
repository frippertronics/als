set(LIBRARY_FILENAME gpio)

add_library(${LIBRARY_FILENAME} OBJECT gpio.c)
target_include_directories(${LIBRARY_FILENAME} PUBLIC ../include)
