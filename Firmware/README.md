## Install baremetal toolchain

`sudo apt-get install gcc-arm-none-eabi make git gcc libudev-dev`

[Download Microchip Advanced Software Framework (latest ASF v3.47)](https://gallery.microchip.com/packages/4CE20911-D794-4550-8B94-6C66A93228B8/3.48.0.1845)

This will allow you to compile the example program
\xdk-asf-3.48.0\sam0\applications\led_toggle\samd21_xplained_pro

Run make on that, should produce /samd21_xplained_pro/gcc/led_toggle_flash.bin

cp ../xdk-asf-3.39.0/sam0/applications/led_toggle/saml21_xplained_pro_b/gcc/led_toggle_flash.bin .
./edbg -b -p -v -f led_toggle_flash.bin -t atmel_cm0p

## Install edbg
[edbg](https://github.com/ataradov/edbg) is a tool for progamming ARM through Atmel edbg-based boards. Install that.

This will produce a binary used to upload code

## Burn firmware

Test the led_toggle_flash.bin by uploading to SamD21 board with the following

`edbg -b -p -v -f led_toggle_flash.bin -t atmel_cm0p`
