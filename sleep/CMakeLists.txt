# This file illustrates how one or more files with .cpp and .hpp-files can be combined 
# in the same library file. Remember to place the accompanying header file in "include/project".

# Define the output library name. Use this name when referencing the library
# in the app and test CMakeLists
set(LIBRARY_FILENAME sleep)

add_library(${LIBRARY_FILENAME} OBJECT sleep.c)
target_link_libraries(${LIBRARY_FILENAME} PRIVATE interrupt)
target_include_directories(${LIBRARY_FILENAME} PUBLIC ../include)
