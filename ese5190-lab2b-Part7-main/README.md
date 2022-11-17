# ese5190-lab2b-Part7
Aim to modify sequencer to use the PIO as its primary I/O engine, including the ability to R/W any register.

## Analyze
In the sequencer part, we record the output of boot pin through Pyserial. To combine it with PIO as its primary I/O engine, apply the logic analyzer part to boot pin output record and sample its output.

## Working principles
Add ```logic_analyzer.h``` file to ```sequencer.c```, replace the ```gpio_get()``` with ```sample()```.
