# ese5190-lab2b-Part3
Aim to create a 'sequencer' that allows you to record BOOT button presses and play them on the Neopixel, and also play a sequence of read/write commands. 

## Working Principles
Choose the mode from the serial consoles, 'R' represents read mode, 'W' represents write mode, and ‘G’ represents modify register mode. 

### Read mode: 
In read mode a limited time is set (as there is a list with 1000 elements to store the output of the boot pin) to record the 
the output, and this record will be saved to 'test.txt' file.

### Write mode
This mode is applied to toggle the led.

### Modify register mode
Combined with repl, this mode is applied to read or write the register value throught the serial consoles.
