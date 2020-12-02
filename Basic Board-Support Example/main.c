/* 
 * main.c
 */

#include "bsp.h"

int main()
{
  /* Configure GPIO */
  pin_setup(GPIODATA_F, RED_LED, OUTPUT);
  pin_setup(GPIODATA_F, BLUE_LED, OUTPUT);
  pin_setup(GPIODATA_F, GREEN_LED, OUTPUT);
  pin_setup(GPIODATA_F, WHITE_LED, OUTPUT);
  pin_setup(GPIODATA_F, SW1, INPUT);
  pin_setup(GPIODATA_F, SW2, INPUT);
  while(1)
  {
    /* Only Light Red LED */
    pin_on(GPIODATA_F, RED_LED);
    pin_off(GPIODATA_F, BLUE_LED);
    delay(1000000);
    
    /* Only Light Blue LED */
    pin_off(GPIODATA_F, RED_LED);
    pin_on(GPIODATA_F, BLUE_LED);
    delay(1000000);
    pin_off(GPIODATA_F, RED_LED);
    pin_off(GPIODATA_F, BLUE_LED);
    
    /* If Button 1 Pressed Only Light Green LED */
    if(pin_read(GPIODATA_F, SW1) == 1)
    {
      pin_on(GPIODATA_F, GREEN_LED);
      delay(3000000);
      pin_off(GPIODATA_F, GREEN_LED);
    }
    
    /* If Button 2 Pressed Only Light White LED */
    if(pin_read(GPIODATA_F, SW2) == 1)
    {
      pin_on(GPIODATA_F, WHITE_LED);
      delay(3000000);
      pin_off(GPIODATA_F, WHITE_LED);
    }
  }
}
