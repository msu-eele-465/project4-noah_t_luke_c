#include "intrinsics.h"
#include <stdbool.h>
#include <string.h>

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

int blink_status = 1;
int cursor_status = 1;
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

    P2DIR |= BIT6;
    P2OUT &= ~BIT6;
}

// Brings cursor to last position on LCD screen
void final_pos()
{
    return_home();
    int i = 0;
    for(i = 0; i<55; i++)
    {
        cursor_right();
    } 
}

void lcd_setup()
{
    lcd_write(0b00100010);
    __delay_cycles(500);
    P1OUT &= ~BIT4;
    P1OUT |= BIT1;
    P1OUT |= BIT0;
    P1OUT &= ~BIT5;
    P1OUT |= BIT6;
    __delay_cycles(1000);
    P1OUT &= ~BIT6;
    __delay_cycles(500);
    lcd_write(0b00001111);
    lcd_write(0b00000001);
    __delay_cycles(10000);
    lcd_write(0b00000110);
}

void cursor_right()
{
    P2OUT &= ~BIT0;
    lcd_write(0b00010100);
    __delay_cycles(500);
    P2OUT |= BIT0;
}

// Toggle the blink functionality of the LCD cursor
void blink_toggle()
{   
    P2OUT &= ~BIT0;
    __delay_cycles(500);
    if(blink_status == 1)
    {
        if(cursor_status = 0)
        {
            lcd_write(0b00001100);
        }
        else if(cursor_status = 1)
        {
            lcd_write(0b00001110);
        }
        blink_status = 0;
    }
    else if(blink_status == 0)
    {
        if(cursor_status = 0)
        {
            lcd_write(0b00001101);
        }
        else if(cursor_status = 1)
        {
            lcd_write(0b00001111);
        }
        blink_status = 1;
    }   
    __delay_cycles(500);
    P2OUT |= BIT0;
}

// Toggle the LCD cursor on/off
void cursor_toggle()
{
    P2OUT &= ~BIT0;
    __delay_cycles(500);
    if(cursor_status == 1)
    {
        if(blink_status = 0)
        {
            lcd_write(0b00001100);
        }
        else if(blink_status = 1)
        {
            lcd_write(0b00001101);
        }
        cursor_status = 0;
    }
    else if(cursor_status == 0)
    {
        if(blink_status = 0)
        {
            lcd_write(0b00001110);
        }
        else if(blink_status = 1)
        {
            lcd_write(0b00001111);
        }
        cursor_status = 1;
    }   
    __delay_cycles(500);
    P2OUT |= BIT0;
}

void clear_cgram()
{
    P2OUT &= ~BIT0;
    lcd_write(0b00000001);
    P2OUT |= BIT0;
}

void return_home()
{
    P2OUT &= ~BIT0;
    lcd_write(0b00000010);
    P2OUT |= BIT0;
}


void lcd_write(int in)
{
        __delay_cycles(500);
        if(CHECK_BIT(in,7) != 0){
            P1OUT |= BIT1;
        } else{
            P1OUT &= ~BIT1;
        }
        if(CHECK_BIT(in,6) != 0){
            P1OUT |= BIT0;
        } else{
            P1OUT &= ~BIT0;
        }
        if(CHECK_BIT(in,5) != 0){
            P1OUT |= BIT4;
        } else{
            P1OUT &= ~BIT4;
        }
        if(CHECK_BIT(in,4) != 0){
            P1OUT |= BIT5;
        } else{
            P1OUT &= ~BIT5;
        }
        __delay_cycles(500);
        P1OUT |= BIT6;
        __delay_cycles(1000);
        P1OUT &= ~BIT6;
        __delay_cycles(500);
        if(CHECK_BIT(in,3) != 0){
            P1OUT |= BIT1;
        } else{
            P1OUT &= ~BIT1;
        }
        if(CHECK_BIT(in,2) != 0){
            P1OUT |= BIT0;
        } else{
            P1OUT &= ~BIT0;
        }
        if(CHECK_BIT(in,1) != 0){
            P1OUT |= BIT4;
        } else{
            P1OUT &= ~BIT4;
        }
        if(CHECK_BIT(in,0) != 0){
            P1OUT |= BIT5;
        } else{
            P1OUT &= ~BIT5;
        }   
        __delay_cycles(500);
        P1OUT |= BIT6;
        __delay_cycles(1000);
        P1OUT &= ~BIT6;
        __delay_cycles(500);
}