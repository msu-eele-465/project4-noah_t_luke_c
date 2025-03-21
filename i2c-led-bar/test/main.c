#include <msp430.h>

unsigned char RXData0=0;
unsigned char RXData1=0;
unsigned char RXData2=0;
unsigned char RXData3=0;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                             // Stop watchdog timer

    // Configure Pins for I2C
    P1SEL0 |= BIT2 | BIT3;                                // I2C pins

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    // Configure USCI_B0 for I2C mode
    UCB0CTLW0 |= UCSWRST;                                 //Software reset enabled
    UCB0CTLW0 |= UCMODE_3;                                //I2C slave mode, SMCLK
    UCB0I2COA0 = 0x0A | UCOAEN;                           //SLAVE0 own address is 0x0A| enable
    UCB0I2COA1 = 0x0B | UCOAEN;                           //SLAVE1 own address is 0x0B| enable
    UCB0I2COA2 = 0x0C | UCOAEN;                           //SLAVE2 own address is 0x0C| enable
    UCB0I2COA3 = 0x0D | UCOAEN;                           //SLAVE3 own address is 0x0D| enable
    UCB0CTLW0 &=~UCSWRST;                                 //clear reset register

    UCB0IE |=  UCRXIE0 | UCRXIE1| UCRXIE2 | UCRXIE3;      //receive interrupt enable

    __bis_SR_register(LPM0_bits | GIE);                   // Enter LPM0 w/ interrupts
    __no_operation();

    
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
        RXData0 = UCB0RXBUF;                              // Get RX data
                               // Vector 24: RXIFG0 break;
    

}
