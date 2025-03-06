Main Loop Software

disable interrupts
call lockKeypad
enable interrupts

ISR TB0CCTL0
heartbeat LED on port 1.1

ISR TB0CCTL1
continually scan what the current input is,
change output based on current selection
send output through I2C

ISR PORT2
Activate on keypress
change current selection variable
exit



