/* 
 * bsp.c (Board Support)
 */

#include "bsp.h"

/*
 * Enable clocking for port
 * OUTPUT -> set pin bit
 * INPUT -> clear pin bit
 *       -> unlock
 *       -> commit
 * Enable  GPIO -> set pin bit
 */
void pin_setup(unsigned int port, unsigned int pin, unsigned int pin_state)
{
  *((unsigned int*) RCGCGPIO) |= 0x1U << 5;
  switch(pin_state)
  {
  case OUTPUT:
    *((unsigned int*) GPIODIR(port)) |= pin;
    break;
  case INPUT:
    *((unsigned int*) GPIODIR(port)) &= ~pin;
    *((unsigned int*) GPIOUNLOCK(port)) = UNLOCK_VAL;
    *((unsigned int*) GPIOCOMMIT(port)) = COMMITALL_VAL;
    break;
  }
  *((unsigned int*) GPIODEN(port)) |= pin;
}

/* 
 * Turn on pin by setting the pin bit in the
 * masked address register of the GPIO Base and pin
 */
void pin_on(unsigned int port, unsigned int pin)
{
  *((unsigned int*) GPIODATA_MASK(port, pin)) |= pin;
}

/* 
 * Turn off pin by clearing the pin bit in the
 * masked address register of the GPIO Base and pin
 */
void pin_off(unsigned int port, unsigned int pin)
{
  *((unsigned int*) GPIODATA_MASK(port, pin)) &= ~pin;
}

/* 
 * Decrement timout passed until it is 0
 */
void delay(unsigned int timeout)
{
  while(timeout != 0)
  {
    --timeout;
  }
}
