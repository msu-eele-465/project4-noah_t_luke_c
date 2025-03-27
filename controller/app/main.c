

#include <msp430fr2355.h>
#include <stdbool.h>
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
    }


}

//------------------------------------------------------------------------------
//           Interrupt Service Routines
//------------------------------------------------------------------------------

#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_CCR0(void) {
    P1OUT ^= BIT0;  // Toggle LED
    TB0CCTL0 &= ~CCIFG;  // Clear the interrupt flag
