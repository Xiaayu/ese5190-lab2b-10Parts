#include "APDS9960.h"
#include "pio_i2c.h"

#define IS_RGBW true
#define NUM_PIXELS 150

#ifdef PICO_DEFAULT_WS2812_PIN
#define WS2812_PIN PICO_DEFAULT_WS2812_PIN
#else
// default to pin 11 if the board doesn't have a default WS2812 pin defined
#define WS2812_PIN 11
#endif

#define PIN_SDA 22
#define PIN_SCL 23

const int addr = 0x39;

void set_neopixel_color(uint32_t color){

    const uint POWER_PIN = 12;
    gpio_init(POWER_PIN);
    gpio_set_dir(POWER_PIN, GPIO_OUT);
    gpio_put(POWER_PIN,1);
    
    PIO pio = pio1;
    int sm = 1;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);
    
    uint32_t result=((uint32_t)(color&0xff0000) >>8) | ((uint32_t)(color&0x00ff00)<<8) | ((uint32_t)(color&0x0000ff));


    pio_sm_put_blocking(pio1, 1, result << 8u);
    if(result==0){
        printf("Lights out.\n");
    }else{
        printf("Lights up!\n");
    }
    pio_clear_instruction_memory(pio1);
    return;
}

uint32_t rgb_to_neopixel(uint8_t r, uint8_t g, uint8_t b){
    uint32_t result = 0;
    result |= (uint32_t)r << 16u;
    result |= (uint32_t)g << 8u;
    result |= (uint32_t)b;
    return result;
}

struct Info{
    int32_t r;
    int32_t g;
    int32_t b;
    int32_t c;
    int32_t proximity;
};

void readInfo(struct Info* info, PIO pio, uint sm, uint8_t addr, bool nostop){
    read_proximity(&info->proximity, pio, sm, addr, nostop);
    read_rgbc(&info->r, &info->g, &info->b, &info->c, pio, sm, addr, nostop);
    // Print out the values
    printf("Proximity: %d, red: %d, green: %d, blue: %d, clear: %d\n", info->proximity, info->r, info->g, info->b, info->c);
}

int main(){
    stdio_init_all();
    sleep_ms(5000);
    printf("=========");

    PIO pio_0 = pio0;
    uint sm_0 = 0;

    uint offset_0 = pio_add_program(pio_0, &i2c_program);
    i2c_program_init(pio_0, sm_0, offset_0, PIN_SDA, PIN_SCL);
    
    APDS9960_init(pio_0, sm_0, addr, false);
    
    printf("APDS9960 initialized\n");
    
    struct Info info;
    while(true){
        printf("The color information :");

        sleep_ms(100);

        readInfo(&info, pio_0, sm_0, addr, false);

        set_neopixel_color(rgb_to_neopixel(info.r, info.g, info.b));

        printf("Color set.\n");
    }

}
