#include "pico/stdlib.h"
#include <stdio.h>
#include "neopixel.h"
#include "hardware/gpio.h"
#include "repl.h"

#define QTPY_BOOT_PIN 21

const uint CAPTURE_PIN_BASE = 21;
const uint CAPTURE_N_SAMPLES = 96;


volatile uint32_t * boot_pin_address;
uint32_t full_gpio_register_value;
uint32_t pin_21_selection_mask;
uint32_t select_pin_state;
uint32_t shifted_pin_21_state;

typedef struct {
    uint32_t last_serial_byte;
    uint32_t button_is_pressed;
    uint32_t light_color;
} Flashlight; 

void render_to_console(Flashlight status) {
    // adjust console window height to match 'frame size'
    for (uint8_t i=0; i<10; i++) { 
        printf("\n");
    }

    printf("button_is_pressed:  0x%08x\n",   status.button_is_pressed);
    printf("light_color:        0x%08x\n",   status.light_color);
}  

// record the boot pin to ram (capture buffer)
void record_pin(uint8_t *capture_buf, uint pin_base, uint n_sample) {
    for (int index = 0; index < n_sample; ++index)
    {
        capture_buf[index] = !(gpio_get(pin_base)); 
        sleep_ms(10);
    }
}

// print out th recording buffer
void print_capture_buf(const uint8_t *buf, uint pin_base, uint n_sample) {
    for (int index = 0; index < n_sample; ++index){ printf("%d",buf[index]);}
    printf("\n");
}

// clear out the buffer
void clear_buffer(uint8_t *buf, uint length){
    for (int index = 0; index < n_sample; ++index)
    {
        capture_buf[index] = 0; 
        sleep_ms(10);
    }
}

// main part of this program
int main() {

    stdio_init_all();
    gpio_init(QTPY_BOOT_PIN);
    gpio_set_dir(QTPY_BOOT_PIN, GPIO_IN);
    neopixel_init();

    Flashlight status;
    status.last_serial_byte =  0x00000000;
    status.button_is_pressed = 0x00000000;
    status.light_color =       0x000000ff;
    char input;

    while (true) {
        status.last_serial_byte = getchar_timeout_us(0); // don't block main loop
        switch(status.last_serial_byte) { // poll every cycle
            
            case 'r':
                while (1){
                input = getchar_timeout_us(0);
                if (input == 's'){break;};
                if (gpio_get(QTPY_BOOT_PIN)){printf("1\n");}
                else {printf("0\n");}
                sleep_ms(100);
                }

            case 'w':
                while (1){
                    input = getchar_timeout_us(0);
                    if (input == 's') {break;}
                    else if (input == '0') {neopixel_set_rgb(0x00ffffff);}
                    else if (input == '1') {neopixel_set_rgb(0x00000000);}
                    sleep_ms(100);
                }

            case 'g':
                while (1){
                    register_modify();
                    sleep_ms(100);
                    break;
                }

            // recording to the ram
            case 'h':
                // record the boot pin
                record_pin(capture_buf, CAPTURE_PIN_BASE, CAPTURE_N_SAMPLES);
                print_capture_buf(capture_buf, CAPTURE_PIN_BASE, CAPTURE_N_SAMPLES);
                clear_buffer(capture_buf, CAPTURE_N_SAMPLES);
                break;
        }
        sleep_ms(10); // don't DDOS the serial console
    }
    return 0;}               
