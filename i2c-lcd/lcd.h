#include "intrinsics.h"
#include <stdbool.h>
#include <string.h>

void DB_on(int sel);
void DB_off(int sel);
/*
    Pins 1.2-1.5 are connected to the data pins on the LCD.
    Pin 1.1 = DB7
    Pin 1.0 = DB6
    Pin 1.4 = DB5
    Pin 1.5 = DB4
    DB0-3 are unused
    
    //Pin to LCD
    //Pin 1.6 = E
    //Pin 1.7 = R/W
    //Pin 2.0 = RS
    */

void lcd_init()
{
    P1DIR |= BIT1;  
    P1OUT &= ~BIT1;  
    P1DIR |= BIT0;  
    P1OUT &= ~BIT0;  
    P1DIR |= BIT4;  
    P1OUT &= ~BIT4;  
    P1DIR |= BIT5;  
    P1OUT &= ~BIT5;
    P1DIR |= BIT6;
    P1OUT &= ~BIT6;  
    P1DIR |= BIT7;  
    P1OUT &= ~BIT7;  
    P2DIR |= BIT0;  
    P2OUT &= ~BIT0;
}

void lcd_setup()
{
    
    __delay_cycles(500);
    DB5(1);
    DB7(1);
    DB6(1);
    DB4(0);
    P1OUT |= BIT6;
    __delay_cycles(1000);
    P1OUT &= ~BIT6;
    __delay_cycles(500);
    DB5(1);
    DB7(1);
    DB6(1);
    DB4(0);
    P1OUT |= BIT6;
    __delay_cycles(1000);
    P1OUT &= ~BIT6;
    __delay_cycles(500);
    DB5(0);
    DB7(0);
    DB6(0);
    DB4(0);
    P1OUT |= BIT6;
    __delay_cycles(1000);
    P1OUT &= ~BIT6;
    __delay_cycles(500);
    DB5(0);
    DB7(0);
    DB6(0);
    DB4(0);
    P1OUT |= BIT6;
    __delay_cycles(1000);
    P1OUT &= ~BIT6;
    __delay_cycles(500);
    DB5(0);
    DB7(1);
    DB6(1);
    DB4(1);
    P1OUT |= BIT6;
    __delay_cycles(1000);
    P1OUT &= ~BIT6;
    __delay_cycles(500);
    DB5(0);
    DB7(0);
    DB6(0);
    DB4(0);
    P1OUT |= BIT6;
    __delay_cycles(1000);
    P1OUT &= ~BIT6;
    __delay_cycles(500);
    DB5(0);
    DB7(0);
    DB6(0);
    DB4(1);
    P1OUT |= BIT6;
    __delay_cycles(1000);
    P1OUT &= ~BIT6;
    __delay_cycles(10000);
    DB5(0);
    DB7(0);
    DB6(0);
    DB4(0);
    P1OUT |= BIT6;
    __delay_cycles(1000);
    P1OUT &= ~BIT6;
    __delay_cycles(500);   
    DB7(0);
    DB6(1);
    DB5(1);
    DB4(0);
    P1OUT |= BIT6;
    __delay_cycles(1000);
    P1OUT &= ~BIT6;


    
}

void DB7(int status)
{
    
    if(status == 1)
    {
        P1OUT |= BIT1; 
    }
    else 
    {
        P1OUT &= ~BIT1;
    }
}

/*
Function to change output of DB6 depending on int input.
*/
void DB6(int status)
{
    if(status == 1)
    {
        P1OUT |= BIT0; 
    }
    else 
    {
        P1OUT &= ~BIT0;
    }
}

/*
Function to change output of DB5 depending on int input.
*/
void DB5(int status)
{
    if(status == 1)
    {
        P1OUT |= BIT4; 
    }
    else 
    {
        P1OUT &= ~BIT4;
    }
}

/*
Function to change output of DB4 depending on int input.
*/
void DB4(int status)
{
    if(status == 1)
    {
        P1OUT |= BIT5; 
    }
    else 
    {
        P1OUT &= ~BIT5;
    }
}

void cursor_right()
{
    //lcd_setup();
    
    __delay_cycles(1);
    DB7(0);
    DB6(0);
    DB5(0);
    DB4(0);
    P1OUT |= BIT6;
    __delay_cycles(500);
    P1OUT &= ~BIT6;
    __delay_cycles(5000);
    __delay_cycles(1);
    DB7(0);
    DB6(1);
    DB5(0);
    DB4(0);
    P1OUT |= BIT6;
    __delay_cycles(500);
    P1OUT &= ~BIT6;
    __delay_cycles(5000);
}

void clear_cgram()
{
    P2OUT &= ~BIT0;
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
    P1OUT |= BIT6;
    __delay_cycles(500);
    DB7(0);
    DB6(0);
    DB5(0);
    DB4(1);
    __delay_cycles(500);
    P1OUT &= ~BIT6;
    __delay_cycles(500);
    P2OUT |= BIT0;
}

void return_home()
{
    P2OUT &= ~BIT0;
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
    P1OUT |= BIT6;
    __delay_cycles(500);
    DB7(0);
    DB6(0);
    DB5(1);
    DB4(0);
    __delay_cycles(500);
    P1OUT &= ~BIT6;
    __delay_cycles(500);
    P2OUT |= BIT0;
}


void lcd_write(int in)
{
        __delay_cycles(500);
        P1OUT |= BIT6;
        __delay_cycles(500);
        if(CHECK_BIT(in,7) != 0){
            DB7(1);
        } else{
            DB7(0);
        }
        if(CHECK_BIT(in,6) != 0){
            DB6(1);
        } else{
            DB6(0);
        }
        if(CHECK_BIT(in,5) != 0){
            DB5(1);
        } else{
            DB5(0);
        }
        if(CHECK_BIT(in,4) != 0){
            DB4(1);
        } else{
            DB4(0);
        }
        __delay_cycles(500);
        P1OUT &= ~BIT6;
        __delay_cycles(500);
        P1OUT |= BIT6;
        __delay_cycles(500);
        if(CHECK_BIT(in,3) != 0){
            DB7(1);
        } else{
            DB7(0);
        }
        if(CHECK_BIT(in,2) != 0){
            DB6(1);
        } else{
            DB6(0);
        }
        if(CHECK_BIT(in,1) != 0){
            DB5(1);
        } else{
            DB5(0);
        }
        if(CHECK_BIT(in,0) != 0){
            DB4(1);
        } else{
            DB4(0);
        }   
        __delay_cycles(500);
        P1OUT &= ~BIT6;
        __delay_cycles(500);
}