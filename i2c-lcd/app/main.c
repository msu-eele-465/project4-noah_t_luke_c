#include "intrinsics.h"
#include <msp430.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <lcd.h>

unsigned char data = 0;
int main(void) { 
    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer

    P1SEL0 |= BIT2 | BIT3;  // Pins for I2C

    UCB0CTLW0 |= UCSWRST;                                 //Software reset enabled
    UCB0CTLW0 |= UCMODE_3;                                //I2C slave mode, SMCLK
    UCB0I2COA0 = 0x0A | UCOAEN;                           //SLAVE0 own address is 0x0A| enable
    UCB0CTLW0 &=~UCSWRST;                                 //clear reset register

    UCB0IE |=  UCRXIE0;      //receive interrupt enable

    PM5CTL0 &= ~LOCKLPM5;  // Enable GPIO

    __enable_interrupt();  // Enable global interrupts
    lcd_init();
    lcd_setup();
    __delay_cycles(500);
    clear_cgram();
    return_home();
    
    while(1)
    {
        /*
        lcd_write(0x4C);
        lcd_write(0b01001111);
        lcd_write(0b01000011);
        lcd_write(0b01001011);
        lcd_write(0b01000101);
        lcd_write(0b01000100);
    }
}

#pragma vector = USCI_B0_VECTOR
__interrupt void USCIB0_ISR(void)
{
    RXData0 = UCB0RXBUF;
    lcd_write(0b01001111);
}

