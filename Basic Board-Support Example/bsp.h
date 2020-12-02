/* 
 * bsp.h (Board Support)
 */

#ifndef BSP_H_
#define BSP_H_

#define SW1 (0x10U)
#define RED_LED (0x02U)
#define BLUE_LED (0x04U)
#define GREEN_LED (0x08U)
#define SW2 (0x01U)

#define GPIODATA_F  (0x40025000U)

#define RCGCGPIO (0x400FE000U + 0x608U)
#define GPIODIR(base) ((base) + 0x400U)
#define GPIODEN(base) ((base) + 0x51CU)
#define GPIOPUR(base) ((base) + 0x510U) 
#define GPIOPDR(base) ((base) + 0x514U)
#define GPIOUNLOCK(base) ((base) + 0x520U)
#define GPIOCOMMIT(base) ((base) + 0x524U)
#define GPIODATA_MASK(base, pin) ((base) + (pin << 2))

#define INPUT (0x00U)
#define OUTPUT (0x01U)

#define UNLOCK_VAL (0x4C4F434BU)
#define COMMITALL_VAL (0xFFU)

void pin_setup(unsigned int port, unsigned int pin, unsigned int pin_state);
void pin_on(unsigned int port, unsigned int pin);
void pin_off(unsigned int port, unsigned int pin);

void delay(unsigned int timeout);

#endif /* BSP_H_ */