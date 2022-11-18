cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(ws2812.c)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})
pico_sdk_init()
include(example_auto_set_url.cmake)

add_executable(ws2812.c)

pico_generate_pio_header(ws2812.c ${CMAKE_CURRENT_LIST_DIR}/i2c.pio)
pico_generate_pio_header(ws2812.c ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)

target_sources(ws2812.c PRIVATE
        pio_i2c.c
        pio_i2c.h
        APDS9960.c
        APDS9960.h
        )

pico_enable_stdio_usb(ws2812.c 1) 
pico_enable_stdio_uart(ws2812.c 0) 

target_link_libraries(ws2812.c PRIVATE pico_stdlib hardware_pio)
pico_add_extra_outputs(ws2812.c)

