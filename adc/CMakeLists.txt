set(LIBRARY_FILENAME adc)

add_library(${LIBRARY_FILENAME} OBJECT adc.c)
target_link_libraries(${LIBRARY_FILENAME} PRIVATE board)
target_include_directories(${LIBRARY_FILENAME} PUBLIC ../include)
