# VT-69 Portable Terminal


![Front View Image](https://github.com/ViolenceWorks/VT-69/blob/main/Web-Assets/FullFrontal.png)

The VT-69 is a portable, battery-powered dumb terminal, along the lines of a VT-100, VT-220, Wyse WY-50, or other such microprocessor-controlled dumb terminals of the mid-80s to mid-90s. It's a portable shell, or a game console that only plays text-based adventures.

Features include:
* 4" LCD with 800x480 resolution
  * Display allows for a full 80x24 character display. *This is not a graphical display*. It will only display text characters.
  * 65536 colors, all of them.
* Silicone membrane keyboard
  * 69 keys. That's why it's the VT-69.
  * Custom-desinged, it's like the keypad on a remote control
  * Other keyboard layouts supported; DVORAK, QWERTZ, and AZERTY are simply a matter of keyboard legends.
* Battery power
  * Internal LiPo battery (> 2000 mAh) is charged from USB-C connector.
  * Provides > 12 hours of battery life.
* Microcontroller
  * ATSAMD51 clocked at blistering 120MHz
  * Custom software libraries allow for fastest text rendering possible	
* Connectivity
  * DE-9 RS-232 serial connector, provided with MAX3232
  * Serial output over USB-C connector
  * Internal UART connectors allow for internal connection to $Single Board Computer$ (a la VT-180) or any other development board with a 'standard' 40-pin header.
  * Hardware handshaking in both DE-9 RS-232 port and internal header
  * Supports _almost_ every terminal escape code recognized by the Linux console.
* Documentation
  * [Many pages of documentation](https://github.com/ViolenceWorks/VT-69/blob/main/Documentation/README.md)
  
![Side View Image](https://github.com/ViolenceWorks/VT-69/blob/main/Web-Assets/SideViewRender.png)
