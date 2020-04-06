Install baremetal toolchain
---------------------------

Install gcc-arm-none-eabi:
	sudo apt-get install gcc-arm-none-eabi   /console

Install make
	sudo apt-get install make

Install git
	sudo apt-get install git

Install gcc


Install libudev
	sudo apt-get install libudev-dev

Download Microchip Advanced Software Framework (latest ASF v3.47)

https://gallery.microchip.com/packages/4CE20911-D794-4550-8B94-6C66A93228B8/3.48.0.1845

cp ../xdk-asf-3.39.0/sam0/applications/led_toggle/saml21_xplained_pro_b/gcc/led_toggle_flash.bin .
./edbg -b -p -v -f led_toggle_flash.bin -t atmel_cm0p

