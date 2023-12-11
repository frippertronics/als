set(LIBRARY_FILENAME gpio)

add_library(${LIBRARY_FILENAME} OBJECT gpio.c)
target_link_libraries(${LIBRARY_FILENAME} PRIVATE board)
target_include_directories(${LIBRARY_FILENAME} PUBLIC ../include)
