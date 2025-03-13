#include "intrinsics.h"
#include <msp430.h>
#include <stdbool.h>
#include <string.h>
#include <lcd.h>


int main(void) { 
    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer

      
   


    PM5CTL0 &= ~LOCKLPM5;  // Enable GPIO

    __enable_interrupt();  // Enable global interrupts
    lcd_init();
    lcd_setup();
    //cursor_right();
    
    while(1)
    {      
        //cursor_right();
        P2OUT |= BIT0;
        __delay_cycles(500);
        P1OUT |= BIT6;
        __delay_cycles(500);
        DB7(0);
        DB6(0);
        DB5(1);
        DB4(1);
        __delay_cycles(500);
        P1OUT &= ~BIT6;
        __delay_cycles(500);
        P1OUT |= BIT6;
        __delay_cycles(500);
        DB7(0);
        DB6(0);
        DB5(0);
        DB4(0);
        __delay_cycles(500);
        P1OUT &= ~BIT6;
        __delay_cycles(500);
        //
        __delay_cycles(1);


    }
}

