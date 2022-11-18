# ese5190-lab2b-Part9

## Intro
In this part we combined the program in part8 with ws2812 to capture its color packet deliver information. Logic analyzer is also applied to obtain the output of ws2812 signal pin.

## Progress
* Initialize I2C and APDS9960
```
  // Apply pio0 for this program
  uint offset = pio_add_program(pio, &i2c_program);

  // Initialize I2C program
  i2c_program_init(pio, sm, offset, PIN_SDA, PIN_SCL);

  sleep_ms(5000);

  // Initialize APDS9960
  APDS9960_init();
```
* Applying WS2812 

Set the neopixel color:
```
void set_neopixel_color(uint32_t color)
```
## Presentation



https://user-images.githubusercontent.com/114005477/202786814-513f48ef-1e39-4513-8665-16030b300f0a.MOV

