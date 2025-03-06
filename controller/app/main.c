<<<<<<< HEAD
#include <msp430.h>
#include "keypad.h"

int main (void){

    keypadInit();

    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer

    P1DIR |= BIT0;  // P1.0 as output, used for heartbeat LED
    P1OUT &= ~BIT0;  // Clear P1.0

    PM5CTL0 &= ~LOCKLPM5;  // Enable GPIO

    // Setup Timer B0
    TB0CTL |= TBCLR;  // Clear timer and dividers
    TB0CTL |= TBSSEL__ACLK;  // Use ACLK
    TB0CTL |= MC__UP;  // Up counting mode
    TB0CCR0 = 32768;    // Compare value

    // Set up timer compare IRQs
    TB0CCTL0 &= ~CCIFG;  // Clear CCR0 flag
    TB0CCTL0 |= CCIE;  // Enable flag

    __enable_interrupt();  // Enable global interrupts

    while(1){
        lockKeypad();
        scanPad();
=======
#include <msp430fr2355.h>
#include <stdbool.h>

int main(void)
{
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    P1OUT &= ~BIT0;
    P1DIR |= BIT0;

    // Disable low-power mode / GPIO high-impedance
    PM5CTL0 &= ~LOCKLPM5;

    while (true)
    {
        P1OUT ^= BIT0;

        // Delay for 100000*(1/MCLK)=0.1s
        __delay_cycles(100000);
>>>>>>> 1af53a2ca29b468e53729ef4dec5c58c354fdd53
    }


}

//------------------------------------------------------------------------------
//           Interrupt Service Routines
//------------------------------------------------------------------------------

#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_CCR0(void) {
    P1OUT ^= BIT0;  // Toggle LED
    TB0CCTL0 &= ~CCIFG;  // Clear the interrupt flag
}