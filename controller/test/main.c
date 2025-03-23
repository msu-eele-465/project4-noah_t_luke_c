#include "intrinsics.h"
#include <msp430.h>
#include <keypad.h>

unsigned char data = 0;
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    
    P1SEL1 &= ~BIT3;
    P1SEL1 &= ~BIT2;
    P1SEL0 |= BIT2 | BIT3;                  // I2C pins
    
    keypadInit();

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    // Configure USCI_B0 for I2C mode
    UCB0CTLW0 |= UCSWRST;                   // Software reset enabled
    UCB0CTLW0 |= UCSSEL__SMCLK;
    UCB0BRW = 10;
    UCB0CTLW0 |= UCMODE_3 | UCMST | UCTR; // I2C mode, Master mode, TX
    //UCB0CTLW1 |= UCASTP_2;                  // Automatic stop generated
                                            // after UCB0TBCNT is reached
    UCB0TBCNT = 0x0001;                     // number of bytes to be received
    UCB0I2CSA = 0x00A;                     // Slave address
    

    // Disable low-power mode / GPIO high-impedance
    PM5CTL0 &= ~LOCKLPM5;
    UCB0CTLW0 &= ~UCSWRST;

    UCB0IE |= UCTXIE0;

    __enable_interrupt();

    while (1)
    {

        /*
        data = 0x0;
        UCB0CTLW0 |= UCTXSTT;
        // Delay for 100000*(1/MCLK)=0.1s
        __delay_cycles(1000000);
        //while (UCB0CTL0 & UCTXSTP);
        data = 0x1;
        UCB0CTLW0 |= UCTXSTT;
        // Delay for 100000*(1/MCLK)=0.1s
        __delay_cycles(1000000);
        //while (UCB0CTL1 & UCTXSTP);
        */
        data = scanPad();
        if(data != 0)
        {
            P1OUT |= BIT0;
        }
    }
}

#pragma vector=EUSCI_B0_VECTOR
__interrupt void EUSCI_B0_I2C_ISR(void){
    P1OUT ^= BIT0;
    UCB0TXBUF = data;

}


