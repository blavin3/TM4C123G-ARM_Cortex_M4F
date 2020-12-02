#Implementation of Board Support Header File
##About the Code
Basic code to control the digital outputs of TM4C123G

Board support files allow the implementation of background and forground software design. Seperate compliation speeds up compile time. 
This also will allow application code be ported to a new device easilyas the bsp would have to be updated to interface with the new device and the apllication code does not need to be changed.
 
##Issues and Limitations
delay(unsigned int timeout) is a simple blocking delay fucntion in future code implemnt one of the timer peripherals to free up CPU i.e. check if an input has changed rather than wait for delay to finish.

##Future Code
