/*
 * libMSP430.h
 *
 * Header file written for the MSP430G2231 Launchpad.
 * It is not guaranteed to work for any other model.
 *
 *  Created on: Oct 21, 2012
 *      Author: Stephen Bennett
 */

#ifndef LIBMSP430_H_
#define LIBMSP430_H_

#include <msp430.h>

#define  MCLK        16000000
#define  SMCLK       16000000

/* Define ACLK Clock Speeds */
#define  ACLK_INT    (12000 / 8)    // Internal ACLK clock speed
#define  ACLK_XTAL   32768          // External crystal clock speed

/*******************************\
|* Public Functions Prototypes *|
\*******************************/
void MSP430_init(void);
void MSP430_timerA0Init(unsigned long time);


/*********************************\
|* Interrupt Function Prototypes *| User defined functionality
\*********************************/
extern void timerA0InterruptHandler(void);

#endif

// vim: tabstop=3 expandtab shiftwidth=3 softtabstop=3
