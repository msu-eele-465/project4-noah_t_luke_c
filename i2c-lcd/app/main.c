#include "intrinsics.h"
#include <msp430.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <lcd.h>

unsigned char RXData = 0;
unsigned char final = 0;


int main(void) { 
    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer

    // Configure Pins for I2C
    P1SEL0 |= BIT2 | BIT3;                                // I2C pins

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    // Configure USCI_B0 for I2C mode
    UCB0CTLW0 |= UCSWRST;                                 //Software reset enabled
    UCB0CTLW0 |= UCMODE_3;                                //I2C slave mode, SMCLK
    UCB0I2COA0 = 0x0A | UCOAEN;                           //SLAVE0 own address is 0x0A| enable
    UCB0CTLW0 &=~UCSWRST;                                 //clear reset register

    UCB0IE |=  UCRXIE0 | UCRXIE1| UCRXIE2 | UCRXIE3;      //receive interrupt enable

    //__bis_SR_register(LPM0_bits | GIE);                   // Enter LPM0 w/ interrupts
    __no_operation();

    PM5CTL0 &= ~LOCKLPM5;  // Enable GPIO


    __enable_interrupt();  // Enable global interrupts
    lcd_init();
    lcd_setup();
    __delay_cycles(500);
    clear_cgram();
    while(1)
    {
        final = RXData;
        // Switch statement prints the pattern description depending on recieved data
        switch(RXData)
        {
            case 0:     break;
            case 0x1:   clear_cgram();
                        lcd_write(0b01110100);
                        lcd_write(0b01101111);
                        lcd_write(0b01100111);
                        lcd_write(0b01100111);
                        lcd_write(0b01101100);
                        lcd_write(0b01100101);
                        RXData = 0;
                        break;
            case 0x2:   clear_cgram();
                        lcd_write(0b01110101);
                        lcd_write(0b01110000);
                        lcd_write(0b11111110);
                        lcd_write(0b01100011);
                        lcd_write(0b01101111);
                        lcd_write(0b01110101);
                        lcd_write(0b01101110);
                        lcd_write(0b01110100);
                        lcd_write(0b01100101);
                        lcd_write(0b01110010);
                        RXData = 0;
                        break;
            case 0x3:   clear_cgram();
                        lcd_write(0b01101001);
                        lcd_write(0b01101110);
                        lcd_write(0b11111110);
                        lcd_write(0b01100001);
                        lcd_write(0b01101110);
                        lcd_write(0b01100100);
                        lcd_write(0b11111110);
                        lcd_write(0b01101111);
                        lcd_write(0b01110101);
                        lcd_write(0b01110100);
                        return_home();
                        RXData = 0;
                        break;
            case 0x10:  clear_cgram();
                        final_pos();
                        lcd_write(0b00111000);
                        int i = 0;
                        for(i = 0; i<0x100; i++)
                        {
                            return_home();
                            lcd_write(i);
                            __delay_cycles(200000);
                        }
                        RXData = 0;
                        break;
            case 0x14:  clear_cgram();
                        lcd_write(0b01110011);
                        lcd_write(0b01110100);
                        lcd_write(0b01100001);
                        lcd_write(0b01110100);
                        lcd_write(0b01101001);
                        lcd_write(0b01100011);
                        RXData = 0;
                        break;
            case 0x16:  clear_cgram();
                        break;
        }
        
        // This switch statement prints the last pressed key to the final position of the LCD
        switch(final)
        {
            case 0:     break;
            case 0x1:   final_pos();
                        lcd_write(0b00110001);
                        break;
            case 0x2:   final_pos();
                        lcd_write(0b00110010);
                        break;
            case 0x3:   final_pos();
                        lcd_write(0b00110011);
                        break;
            case 0x4:   final_pos();
                        lcd_write(0b01000001);
                        break;
            case 0x8:   final_pos();
                        lcd_write(0b01000010);
                        break;
            case 0x11:  blink_toggle();
                        final_pos();
                        lcd_write(0b00111001);
                        break;
            case 0x12:  cursor_toggle();
                        final_pos();
                        lcd_write(0b01000011);
                        break;
            case 0x14:  final_pos();
                        lcd_write(0b00110000);
                        break;
            case 0x16:  break; 
        }
        if(final != 0)
        {
            return_home();
        }
        final = 0;
        

    }
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCI_B0_VECTOR
__interrupt void USCIB0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_B0_VECTOR))) USCIB0_ISR (void)
#else
#error Compiler not supported!
#endif
{
                                       // SLAVE0
        RXData = UCB0RXBUF;                              // Get RX data
        P2OUT ^= BIT6;
        __bic_SR_register_on_exit(LPM0_bits);                       // Vector 24: RXIFG0 break;
    

}