#include <msp430.h>
#include <ledbar.h>

unsigned char RXData=0;
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                             // Stop watchdog timer

    P1DIR |= BIT1;
    P1OUT &= ~BIT1;
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

    __bis_SR_register(LPM0_bits | GIE);                   // Enter LPM0 w/ interrupts
    __no_operation();
    LEDbarInit();
    while(1){
        if(RXData == 0x1)
        {
            pattern0();
        }
        else if(RXData == 0x0)
        {
            pattern0_alt();
        }
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
        __bic_SR_register_on_exit(LPM0_bits);                       // Vector 24: RXIFG0 break;
    

}
