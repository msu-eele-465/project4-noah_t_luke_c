#include <msp430.h>
#include <stdbool.h>

const char keys[4][4] = {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
const char row_pins[4] = {BIT0, BIT1, BIT2, BIT3};
const char col_pins[4] = {BIT0, BIT1, BIT2, BIT3};

void keypadInit(void){

    // Status RGB LED setup
    P1DIR |= BIT1;  // P1.1 as output, RED  
    P1OUT &= ~BIT1;  // Clear P1.1

    P1DIR |= BIT2;  // P1.2 as output, GREEN
    P1OUT &= ~BIT2;  // Clear P1.2

    P1DIR |= BIT3;  // P1.3 as output, BLUE
    P1OUT &= ~BIT3;  // Clear P1.3

    // P6.6 for keypress feedback
    P6DIR |= BIT6; 
    P6OUT &= ~BIT6;  

    // Column pins are 6.0 - 6.3, right 4 pins on Keypad, descending left to right
    // Pin 6.0 is column 0 (connected to the middle of the keypad) (column 0 is the furthest left column)
    // Pin 6.3 is column 3 (connected to the right of the keypad) (column 3 is the furthest right column)
    P6DIR &= ~(BIT0 + BIT1 + BIT2 + BIT3);  // Clear column pins
    P6DIR |= (BIT0 + BIT1 + BIT2 + BIT3);  // Set column pins as outputs
    P6OUT &= ~(BIT0 + BIT1 + BIT2 + BIT3);  // Set column pins low

    // Row pins are 2.0 - 2.3, left 4 pins, descending left to right
    // Pin 2.0 is row 0 (connected to the left of the keypad) (row 0 is the top row)
    // Pin 2.3 is row 3 (connected to the middle of the keypad) (row 3 is the bottom row)
    P2DIR &= ~(BIT0 + BIT1 + BIT2 + BIT3);  // Set row pins as inputs
    P2REN |= (BIT0 + BIT1 + BIT2 + BIT3);  // Enable pull-up/down resistors
    P2OUT &= ~(BIT0 + BIT1 + BIT2 + BIT3);  // Set pull-down for resistors
}

//-----------------------------------------------Scan Keypad------------------------------------------------------------------------

void lockKeypad(){
        P1OUT |= BIT1;

        while(scanPad() != '1');
        P1OUT &= ~BIT1;
        P1OUT |= BIT2;

        while(scanPad() != '7');

        while(scanPad() != '3');

        while(scanPad() != '8');
        P1OUT &= ~BIT1;
        P1OUT &= ~BIT2;
        P1OUT |= BIT3;





}

char scanPad() {
    int row, col;  // Loop variables

    for (col = 0; col < 4; col++) {
        P6OUT &= ~(BIT0 | BIT1 | BIT2 | BIT3);  // Clear all column pins
        P6OUT |= col_pins[col];  // Set the current column pin high

        for (row = 0; row < 4; row++) {
            if ((P2IN & row_pins[row]) != 0) {  // Check if the row pin is high
                while ((P2IN & row_pins[row]) != 0);  // Wait for key release
                __delay_cycles(50000);  // Debounce delay
                P6OUT ^= BIT6;
                return keys[row][col];  // Return the pressed key
            }
        }
    }

    return 0;  // Return 0 if no key is pressed
}

