/* 
 * Controlling Port F1, F2 and F3 outputs 
 *
 * Built in LEDs on Tiva C
 *
 * Red LED -> PF1 (GPIO base addresses assigned to Advanced Peripheral Bus)
 * Blue LED -> PF2
 * Green LED -> PF3
 *
 * Masked addresses for each pin can be used in the future to prevent
 * race conditions
 *
 * Breakpoint placed at start of while to step through each line to observe
 * LEDs turn on and off 
 *
 */

#define RED_LED (0x02U)
#define BLUE_LED (0x04U)
#define GREEN_LED (0x08U)

#define GPIODATA_F  (0x40025000U)
#define RCGCGPIO (0x400FE000U+0x608U)
#define GPIODIR (GPIODATA_F + 0x400U)
#define GPIODEN (GPIODATA_F + 0x51CU) 

int main()
{
  /* *** Comments below copied from TM4c123G datasheet *** */
  
  /* 1. Enable the clock to the port by setting the appropriate bits in the RCGCGPIO register (see
  page 340). In addition, the SCGCGPIO and DCGCGPIO registers can be programmed in the
  same manner to enable clocking in Sleep and Deep-Sleep modes. */
  *((unsigned int*) RCGCGPIO) |= (1U << 5); // Enable and provide a clock to GPIO Port F
  
  /* 2. Set the direction of the GPIO port pins by programming the GPIODIR register. A write of a 1
  indicates output and a write of a 0 indicates input. */
  *((unsigned int*) GPIODIR) |= (RED_LED | GREEN_LED | BLUE_LED); 
  
  /* 6. To enable GPIO pins as digital I/Os, set the appropriate DEN bit in the GPIODEN register. To
  enable GPIO pins to their analog function (if available), set the GPIOAMSEL bit in the
  GPIOAMSEL register. */
  *((unsigned int*) GPIODEN) |= (RED_LED | GREEN_LED | BLUE_LED); // Sets PF1, PF2 and PF3 as Outputs
  
  while(1)
  {
    /* Pointer to masked address of Red LED on Port F */
    unsigned int* portf_mask = (unsigned int*)(GPIODATA_F | (RED_LED << 2)); 
    /* RED ON */
    *(portf_mask) |= RED_LED; // Sets red LED bit
    /* RED OFF */
    *(portf_mask) &= ~(RED_LED); // Clears red LED bit perserves other gpio states
    
    /* Change pointer to point at the masked address of Blue Led */
    portf_mask = (unsigned int*)(GPIODATA_F | (BLUE_LED << 2)); 
    /* BLUE ON */
    *(portf_mask) |= BLUE_LED; // Sets blue LED bit
    /* BLUE OFF */
    *(portf_mask) &= ~(BLUE_LED); // Clears blue LED bit
    
    /* Change pointer to point at the masked address of Green Led */
    portf_mask = (unsigned int*)(GPIODATA_F | (GREEN_LED << 2)); 
    /* GREEN ON */
    *(portf_mask) |= GREEN_LED; // Sets green LED bit
    /* GREEN OFF */
    *(portf_mask) &= ~(GREEN_LED); // Clears green LED bit
        
    /* Change pointer to point at the masked address of all Leds */
    portf_mask = (unsigned int*)(GPIODATA_F | ((RED_LED | BLUE_LED | GREEN_LED) << 2)); 
    /* ALL ON (WHITE) */
    *(portf_mask) |= (RED_LED | BLUE_LED | GREEN_LED); // Sets all
    /* ALL OFF */
    *(portf_mask) &= ~(RED_LED | BLUE_LED | GREEN_LED); // Clears all
  }
}
