## Install baremetal toolchain

`sudo apt-get install gcc-arm-none-eabi make git gcc libudev-dev`

[Download Microchip Advanced Software Framework](https://www.microchip.com/mymicrochip/filehandler.aspx?ddocname=en1000272) or you could [find the latest version here](https://www.microchip.com/mplab/avr-support/avr-and-sam-downloads-archive). Look for Advanced Software Framework (ASF) and grab the latest version. Unzip that somewhere.

This will allow you to compile the example program
\xdk-asf-3.48.0\sam0\applications\led_toggle\samd21_xplained_pro

Run make on that, should produce /samd21_xplained_pro/gcc/led_toggle_flash.bin

## Install edbg
[edbg](https://github.com/ataradov/edbg) is a tool for progamming ARM through Atmel edbg-based boards. Install that.

This will produce a binary used to upload code

## Burn firmware

Test the led_toggle_flash.bin by uploading to SamD21 board with the following

`edbg -b -p -v -f led_toggle_flash.bin -t atmel_cm0p`

The toolchain and uploading has been verified on your machine. Now we need a makefile and such for the real code.
