set(TEST_FILES gpio_test.c)

add_executable(suite_1_app
    gpio_test.c
)

target_link_libraries(suite_1_app
    unity
    gpio
)

add_test(suite_1_test suite_1_app)
