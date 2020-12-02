# Implementation of Board Support Header File

## Motivation
* Basic code to control the digital outputs of TM4C123G
* Board support files allow the implementation of background and forground software design. 
* Seperate compliation speeds up compile time as only files that have changed have to be compiled. 
* This also will allow application code be ported to a new device easily as the BSP would have to be updated to interface with the new device. The application code does not have to be updated to interface with the new device
 
## Issues and Limitations
1. Delay function has to finish before any other functions can be executed.
2. Button press is missed if program is executing a function. The button has to be held until the code checks to see if the input bit is set.

## Future Code

* delay(unsigned int timeout) is a simple blocking delay fucntion in future code implemnt one of the timer peripherals to free up CPU i.e. check if an input has changed rather than wait for delay to finish.
