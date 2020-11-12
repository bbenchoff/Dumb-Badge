# VT-69 Portable Terminal

![Side View Image](https://github.com/bbenchoff/Dumb-Badge/blob/master/Web-Assets/SideViewRender.png)

The VT-69 is a portable, battery-powered dumb terminal, along the lines of a VT-100, VT-220, Wyse WY-50, or other such microprocessor-controlled dumb terminals of the mid-80s to mid-90s.

Features include:
* **4" LCD with 800x480 resolution**
  * Display allows for a full 80x24 character display. *This is not a graphical display*. It will only display text characters.
  * Full color. All 256 of them. Only one color at a time.
* Silicone membrane keyboard
  * Custom-desinged keyboard
  * Other keyboard layouts supported; DVORAK, QWERTZ, and AZERTY are simply a matter of keyboard legends.
* Battery power!
  * Internal LiPo battery (> 2000 mAh) is charged from USB-C connector.
  * Provides > 12 hours of battery life.
* Microcontroller
  * Designed around ATSAMD21 clocked at blistering 48MHz
  * Custom software libraries allow for fastest text rendering possible
* Connectivity
  * DE-9 RS-232 serial connector, provided with MAX3232
  * USB 2.0 over USB-C connector
  * Internal UART connectors allow for internal connection to Raspberry Pi Zero (a la VT-180) or any other development board with a 40-pin 'raspi' header.
  
![Front View Image](https://github.com/bbenchoff/Dumb-Badge/blob/master/Web-Assets/FullFrontal.png)
