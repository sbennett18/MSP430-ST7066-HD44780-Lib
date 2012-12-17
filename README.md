MSP430-ST7066-HD44780-Lib
=========================

Library for interfacing MSP430 with a basic character LCD using either the ST7066 or HD44780 controller in 4-bit mode.

Modifying this code to work with the 8-bit interface should be fairly straightforward. Simply adjust the pin definitions (add more as necessary) and adjust the LCD_sendByte command to not split the byte in two.
Some other minor changes to the initialization function may be necessary as well.
