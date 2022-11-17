# ese5190-lab2b-Part1

## Main parts code is showing below:

### 1. Initialize the variables in flashlight.c:
```
volatile uint32_t * boot_pin_address;
uint32_t full_gpio_register_value;
uint32_t pin_21_selection_mask;
uint32_t select_pin_state;
uint32_t shifted_pin_21_state;
```

### 2. Write the boot register address directly
```
 boot_pin_address = (volatile uint32_t *) 0xd0000004;
        full_gpio_register_value = (uint32_t) * boot_pin_address;
        pin_21_selection_mask = 1u << 21;
        select_pin_state = full_gpio_register_value & pin_21_selection_mask;
        shifted_pin_21_state = select_pin_state >> 21;
```

### 3. Initialize PIN and POWER_PIN in nerpixel.c
```
#define PIN         12
#define POWER_PIN   11
```
