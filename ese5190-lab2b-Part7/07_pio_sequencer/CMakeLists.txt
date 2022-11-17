cmake_minimum_required(VERSION 3.13) # CMAKE (heading)
include(pico_sdk_import.cmake) # CMAKE -> PICO SDK (include)

project(pio_sequencer C CXX ASM) # CMAKE ("project")
pico_sdk_init() # PICO SDK (initialization)

add_executable(pio_sequencer) # CMAKE (target)

pico_generate_pio_header(pio_sequencer ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}) # PICO SDK (PIO)

target_sources(pio_sequencer PRIVATE pio_sequencer.c neopixel.c repl.c logic_analyzer.c) # CMAKE -> C (compiler)
target_link_libraries(pio_sequencer PRIVATE pico_stdlib hardware_pio hardware_dma) # CMAKE -> C (linker)

pico_enable_stdio_usb(pio_sequencer 1) # PICO SDK (USB)
pico_enable_stdio_uart(pio_sequencer 0) # PICO SDK (USB)

pico_add_extra_outputs(pio_sequencer) # PICO SDK (UF2)
