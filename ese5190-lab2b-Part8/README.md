# ese5190-lab2b-Part8

## Main parts code is showing below:

### 1. Make some change to i2c.pio
Add ```mov isr, null              ; Reset the input bit counter``` to implement the code:

After finished the code looks like:
```
out pindirs, 1         [7] ; On reads, we provide the ACK.  
    nop             side 1 [7] ; SCL rising edge
    wait 1 pin, 1          [7] ; Allow clock to be stretched
    jmp pin do_nack side 0 [2] ; Test SDA for ACK/NAK, fall through if ACK
    mov isr, null              ; Reset the input bit counter
```

### 2. Make some change to pio_i2c.c
```
pio_i2c_repstart(pio, sm); // replace start with restart
```

### 3. Presentation

<img width="565" alt="截屏2022-11-17 下午6 03 10" src="https://user-images.githubusercontent.com/114005477/202579881-fd400354-06c0-4cfb-8152-8d6c6b3d3f4c.png">
