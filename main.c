/*
 * main.c
 *
 *  Created on: Oct 18, 2012
 *      Author: Stephen Bennett
 */

#include "libMSP430LCD.h"

/***************************************************************************\
|* PUBLIC FUNCTION :: main
|*
|*    Main entry point to the sketch.
|*
|* PARAMETERS
|*
|*    void
|*
|* RETURN
|*
|*    void
|*
\***************************************************************************/
void main(void)
{
   WDTCTL = WDTPW + WDTHOLD;   // Stop watchdog timer
   P1DIR |= BIT6;

   LCD_init();
   LCD_init();

   while (1)
   {
      P1OUT &= ~BIT6; // Turn off the green LED for visual cue

      LCD_clearScreen();

      LCD_printStr("Connor...");
      LCD_setCursorPosition(1, 6);

      _delay_milliseconds(2000);

      LCD_printStr("Wake up!!!");

      P1OUT |= BIT6; // Turn on the green LED for visual cue

      _delay_milliseconds(2000);
   }
}
