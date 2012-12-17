/*
 * libMSP430.c
 *
 * Source file written for the MSP430G2231 Launchpad.
 * It is not guaranteed to work for any other model.
 *
 *  Created on: Oct 21, 2012
 *      Author: Stephen Bennett
 */

#include "libMSP430.h"


/********************\
|* Public Functions *|
\********************/

/*-------------------------------------------------------------------------*\
|* PUBLIC FUNCTION :: MSP430_init
|*
|*    Initialize the MSP430 main control registers.
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
void MSP430_init(void)
{
   /* BCSCTL1 : Basic Clock System Control Register 1
    *
    * DIVAx (5-4) :: Divider for ACLK
    *    00 -- /1 (DIVA_0)
    *    01 -- /2 (DIVA_1)
    *    10 -- /4 (DIVA_2)
    *    11 -- /8 (DIVA_3)
    */
}


/*-------------------------------------------------------------------------*\
|* PUBLIC FUNCTION :: MSP430_timerA2Init
|*
|*    Initialize the MSP430 Timer A2 timer.
|*
|* PARAMETERS
|*
|*    time - time in milliseconds between interrupts
|*
|* RETURN
|*
|*    void
|*
\*-------------------------------------------------------------------------*/
void MSP430_timerA0Init(unsigned long time)
{
   /*=================================
    * TAR : Timer_A Register
    *    Holds the count of Timer_A
    *    16 bits
    */

   /*=================================
    * TACCTLx : Capture/Compare Control Register x [0, 1]
    *
    * CMx (15-14) :: Capture Mode
    *    00 -- No capture                               (CM_0)
    *    01 -- Capture on rising edge                   (CM_1)
    *    10 -- Capture on falling edge                  (CM_2)
    *    11 -- Capture on both rising and falling edges (CM_3)
    *
    * CCISx (13-12) :: Capture/Compare input select - set the TACCRx input signal
    *    00 -- CCIxA (CCIS_0)
    *    01 -- CCIxB (CCIS_1)
    *    10 -- GND   (CCIS_2)
    *    11 -- VCC   (CCIS_3)
    *
    * SCS (11) :: Synchronize capture source
    *    0 -- Asynchronous capture (~SCS)
    *    1 -- Synchronous capture  (SCS)
    *
    * SCCI (10) :: Synchronized capture/compare input - read only
    *
    * Unused (9)
    *
    * CAP (8) :: Capture mode
    *    0 -- Compare mode (~CAP)
    *    1 -- Capture mode (CAP)
    *
    * OUTMODx (7-5) :: Output mode
    *    000 -- OUT bit value (OUTMOD_0)
    *    001 -- Set           (OUTMOD_1)
    *    010 -- Toggle/Reset  (OUTMOD_2)
    *    011 -- Set/Reset     (OUTMOD_3)
    *    100 -- Toggle        (OUTMOD_4)
    *    101 -- Reset         (OUTMOD_5)
    *    110 -- Toggle/Set    (OUTMOD_6)
    *    111 -- Reset/Set     (OUTMOD_7)
    *
    * CCIE (4) :: Capture/Compare Interrupt Enable
    *    Enables interrupt request of corresponding CCIFG flag
    *    0 - Interrupt disabled (~CCIE)
    *    1 - Interrupt enabled  (CCIE)
    *
    * CCI (3) :: Capture/Compare Input - read only
    *    Selected input signal can be read by this bit
    *
    * OUT (2) :: Output - for output mode 0
    *    0 - Output low  (~OUT)
    *    1 - Output high (OUT)
    *
    * COV (1) :: Capture overflow
    *    Indicates a capture overflow occured
    *    COV must be reset with software (writing to this bit I think)
    *    0 - No capture overflow occurred
    *    1 - Capture overflow occurred
    *
    * CCIFG (0) :: Capture/Compare Interrupt Flag
    *    0 - No interrupt pending
    *    1 - Interrupt pending
    */

   /*=================================
    * TACCRx : Timer_A Capture/Compare Register x [0, 1]
    *
    *    Compare Mode:
    *       TACCRx holds the data for the comparison to the timer value in TAR.
    *       Used for timed software interrupts.
    *
    *    Capture Mode:
    *       TAR is copied into the TACCRx register when a capture is performed
    */

   /*=================================
    * TACTL : Timer_A Control Register
    *
    * TASSELx (9-8) :: Timer_A clock source select
    *    00 -- TACLK (TASSEL_0)
    *    01 -- ACLK  (TASSEL_1)
    *    10 -- SMCLK (TASSEL_2)
    *
    * IDx (7-6) :: Input Divider
    *    00 -- /1 (ID_0)
    *    01 -- /2 (ID_1)
    *    10 -- /4 (ID_2)
    *    11 -- /8 (ID_3)
    *
    * MCx (5-4) :: Mode Control/Start Timer (set to 00 when Timer_A not in use to conserve power
    *    00 -- Stop Mode, time is haled (MC_0)
    *    01 -- Up Mode, timer counts up to TACCR0 (MC_1)
    *    10 -- Continous Mode, timer counts up to 0xFFFF (MC_2)
    *    11 -- Up/Down Mode, timer counts up to TACCR0 then down to 0 (MC_3)
    *
    * Unused (3)
    *
    * TACLR (2) :: Timer_A clear - resets TAR, clock divider, and count direction
    *
    * TAIE (1) :: Timer_A interrupt enable - enabled TAIFG interrupt request
    *    0 -- Interrupt disabled
    *    1 -- Interrupt enabled
    *
    * TAIFG (0) :: Timer_A interrupt flag
    *    0 -- No interrupt pending
    *    1 -- Interrupt pending
    */

   TACCTL0 = CM_0 + CCIS_0 + OUTMOD_0 + CCIE;

   /* Approximation: (>> 10) ~=~ (/ 1000) */
   TACCR0 = ( ( time * ACLK_INT ) >> 10 ) - 1;

   TACTL = TASSEL_1 + ID_0 + MC_1;
}


/************************************\
|* Interrupt Vector Initializations *|
\************************************/

/*-------------------------------------------------------------------------*\
|* INTERRUPT :: for MSP430_timerA0Init
|*
|*    Call timerA0InterruptHandler then go back to sleep.
|*
\*-------------------------------------------------------------------------*/
#pragma vector=TIMERA0_VECTOR
__interrupt void TIMERA0_ISR_HOOK(void)
{
   /* Capture Compare Register 0 ISR Hook Function Name */
   timerA0InterruptHandler();

   /* Clear all Low Power Mode (LPM) bits in Status Register (SR).
    * --> Upon exiting ISR, return to last call to enter LPM
    *     and enter Active mode.
    */
   __bic_SR_register_on_exit(LPM4_bits);
}

// vim: tabstop=3 expandtab shiftwidth=3 softtabstop=3
