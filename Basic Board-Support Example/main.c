/* 
 * Basic code to control the digital outputs of TM4C123G
 *
 * Board support files allow the implementation of background
 * and forground software design. Seperate compliation speeds 
 * up compile time. This also will allow application code be 
 * ported to a new device easilyas the bsp would have to be 
 * updated to interface with the new device and the apllication
 * code does not need to be changed.
 *  
 * delay(unsigned int timeout) is a simple blocking delay fucntion
 * in future code implemnt one of the timer peripherals to free up
 * CPU i.e. check if an input has changed rather than wait for delay
 * to finish.
 *
 */

#include "bsp.h"

int main()
{
  pin_setup(GPIODATA_F, RED_LED, OUTPUT);
  pin_setup(GPIODATA_F, BLUE_LED, OUTPUT);
  while(1)
  {
    pin_on(GPIODATA_F, RED_LED);
    pin_off(GPIODATA_F, BLUE_LED);
    delay(1000000);
    pin_off(GPIODATA_F, RED_LED);
    pin_on(GPIODATA_F, BLUE_LED);
    delay(1000000);
  }
}
