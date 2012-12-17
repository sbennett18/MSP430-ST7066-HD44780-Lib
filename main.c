/*
 * main.c
 *
 *  Created on: Oct 18, 2012
 *      Author: Stephen Bennett
 */

#include "libLCD.h"
#include "libMSP430.h"


/*-------------------------------------------------------------------------*\
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
\*-------------------------------------------------------------------------*/
void main(void)
{
   WDTCTL = WDTPW + WDTHOLD;   // Stop watchdog timer

   P1DIR |= BIT6;    // Set BIT6 to be an output (green LED)
   P1OUT &= ~BIT6;   // Turn on the green LED

   /* Initialize timer for a 2s delay -> interrupt and return to code in active mode */
   MSP430_timerA0Init(1000);

   LCD_init();

   while (1)
   {
      LCD_clearScreen();

      LCD_printStr("Connor...");
      LCD_setCursorPosition(1, 6);

      __bis_SR_register(LPM3_bits + GIE);   // Enter LPM3 with General Interrupts Enabled

      LCD_printStr("Wake up!!!");

      __bis_SR_register(LPM3_bits + GIE);   // Enter LPM3 with General Interrupts Enabled
   }
}

void timerA0InterruptHandler(void)
{
   P1OUT ^= BIT6;    // Toggle the green LED for visual cue
}

// vim: tabstop=3 expandtab shiftwidth=3 softtabstop=3
