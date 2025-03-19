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
    __delay_cycles(500);
    clear_cgram();
    return_home();
    
    while(1)
    {
        lcd_write(0x4C);
        lcd_write(0b01001111);
        lcd_write(0b01000011);
        lcd_write(0b01001011);
        lcd_write(0b01000101);
        lcd_write(0b01000100);
    }
}

