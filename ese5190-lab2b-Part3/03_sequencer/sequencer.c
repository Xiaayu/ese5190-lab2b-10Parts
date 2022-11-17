#include "pico/stdlib.h"
#include <stdio.h>
#include "neopixel.h"
#include "hardware/gpio.h"
#include "repl.h"

#define QTPY_BOOT_PIN 21

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
                
            
        }
        sleep_ms(10); // don't DDOS the serial console
    }
    return 0;}               
