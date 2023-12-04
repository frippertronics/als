set(LIBRARY_FILENAME adc)

add_library(${LIBRARY_FILENAME} OBJECT adc.c)
target_include_directories(${LIBRARY_FILENAME} PUBLIC ../include)
