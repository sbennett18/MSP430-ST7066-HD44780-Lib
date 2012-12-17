/*
 * libLCD.h
 *
 * Header file written for Basic 16x2 Character LCD from SparkFun.
 * (https://www.sparkfun.com/products/9053)
 * Should work for any display utilizing the common
 *    ST7066 / HD44780 parallel interface in 4-bit mode.
 * Making this work for 8-bit mode should only require adjusting some
 * of the pin definitions below and adjusting some of the initializations.
 *
 *  Created on: Oct 18, 2012
 *      Author: Stephen Bennett
 */

#ifndef LIBLCD_H_
#define LIBLCD_H_

/****************************\
|* Standard MSP430 includes *|
\****************************/
#include <msp430.h>

/* Microcontroller clock speed - used for timing calculations */
#define     MCU_XTAL_CLK      1000000
#define     MCU_XTAL_TIME     ((MCU_XTAL_CLK) / 1000)

/* Convert milliseconds to clock cycles. */
#define     _delay_milliseconds(msecs) \
               __delay_cycles(((msecs) * (MCU_XTAL_TIME)))


/***************************************\
|* Define Ports Used for Communication *| For now, all pins should be on the same port
\***************************************/
/* Data pins must be on same port */
#define     LCD_DIR_DATA      P1DIR
#define     LCD_OUT_DATA      P1OUT

/* Reg Select Port */
#define     LCD_DIR_RS        P1DIR
#define     LCD_OUT_RS        P1OUT

/* Read/Write Port */
#define     LCD_DIR_RW        P1DIR
#define     LCD_OUT_RW        P1OUT

/* Enable Port */
#define     LCD_DIR_EN        P1DIR
#define     LCD_OUT_EN        P1OUT


/*************************************\
|* Define Pins Used for Communication*|
\*************************************/
/* Data pins must be consecutive & ascending */
#define     LCD_PIN_D4        BIT0
#define     LCD_PIN_D5        BIT1
#define     LCD_PIN_D6        BIT2
#define     LCD_PIN_D7        BIT3

#define     LCD_PIN_RS        BIT5
#define     LCD_PIN_RW        BIT6
#define     LCD_PIN_EN        BIT4

#define     LCD_MASK_DATA     (LCD_PIN_D7 | LCD_PIN_D6 | LCD_PIN_D5 | LCD_PIN_D4)


/*****************************************\
|* Define Useful Display Characteristics *|
\*****************************************/
#define     LCD_NUM_COLS      16
#define     LCD_NUM_ROWS      2


/***************************\
|* Define Display Commands *|
\***************************/
/* Function Set Defines */
#define     FUNCTION_SET      0x20  // Must be set to execute FUNCTION_SET_CMD
#define     INTFC_DATA_LEN    0x10  // HIGH: 8-bit interface | LOW: 4-bit interface
#define     TWO_LINE_DISP     0x08  // HIGH: 2-line display | LOW: 1-line display
#define     CHAR_FONT_SIZE    0x04  // HIGH: 5x10 dots | LOW: 5x8 dots (only usable with 1-line display)
/* Function Set Command - modify to liking */
#define     FUNCTION_SET_CMD  (FUNCTION_SET | TWO_LINE_DISP)

/* Display Initialization Defines */
#define     DISPLAY_ON        0x08  // Must be set to execute DISPLAY_ON_CMD
#define     ENTIRE_DISP_ON    0x04
#define     CURSOR_ON         0x02  // Show the cursor at current position
#define     CURSOR_BLINK_ON   0x01  // Make the cursor blink
/* Display Initialization Command - modify to liking */
#define     DISPLAY_ON_CMD    (DISPLAY_ON | ENTIRE_DISP_ON | CURSOR_ON)

/* Entry Mode Initialization Defines */
#define     ENTRY_MODE        0x04  // Must be set to execute ENTRY_MODE_CMD
#define     CURSOR_INCR       0x02  // Cursor increment on character write, else decrement
#define     DISPLAY_SHIFT_ON  0x01  // Shift display according to CURSOR_INCR
/* Entry Mode Initialization Command - modify to liking */
#define     ENTRY_MODE_CMD    (ENTRY_MODE | CURSOR_INCR)

/* Miscellaneous Commands */
#define     CLEAR_DISP_CMD    0x01  // Clear the display
#define     RET_HOME_CMD      0x02  // Return cursor to top left (0,0)


/****************************\
|* Useful Data Type Defines *|
\****************************/
#define     COMMAND           0
#define     DATA              1
typedef     unsigned char     uint8_t;


/******************************\
|* Public Function Prototypes *|
\******************************/
void LCD_init(void);
void LCD_printStr(char *text);
void LCD_printChar(char character);
void LCD_sendCommand(char command);
void LCD_setCursorPosition(uint8_t row, uint8_t col);
void LCD_clearScreen(void);

#endif

// vim: tabstop=3 expandtab shiftwidth=3 softtabstop=3
