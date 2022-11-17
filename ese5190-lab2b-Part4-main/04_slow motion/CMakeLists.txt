cmake_minimum_required(VERSION 3.13) # CMAKE (heading)
include(pico_sdk_import.cmake) # CMAKE -> PICO SDK (include)

project(Slowmotion C CXX ASM) # CMAKE ("project")
pico_sdk_init() # PICO SDK (initialization)

add_executable(slow_motion) # CMAKE (target)

pico_generate_pio_header(slow_motion ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}) # PICO SDK (PIO)

target_sources(slow_motion PRIVATE slow_motion.c neopixel.c repl.c) # CMAKE -> C (compiler)
target_link_libraries(slow_motion PRIVATE pico_stdlib hardware_pio) # CMAKE -> C (linker)

pico_enable_stdio_usb(slow_motion 1) # PICO SDK (USB)
pico_enable_stdio_uart(slow_motion 0) # PICO SDK (USB)

pico_add_extra_outputs(slow_motion) # PICO SDK (UF2)
