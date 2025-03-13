#include "intrinsics.h"
#include <msp430.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <lcd.h>


int main(void) { 
    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer

      
   


    PM5CTL0 &= ~LOCKLPM5;  // Enable GPIO

    __enable_interrupt();  // Enable global interrupts
    lcd_init();
    lcd_setup();
    //cursor_right();
    __delay_cycles(500);
    clear_cgram();
    return_home();
    //P2OUT |= BIT0;
    
    while(1)
    {      
        //cursor_right();
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
        DB4(1);
        __delay_cycles(500);
        P1OUT &= ~BIT6;
        __delay_cycles(500);


    }
}

