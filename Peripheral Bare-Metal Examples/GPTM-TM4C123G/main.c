/* Periodic timer - Timer0 A (16-bit timer)*/

#define RCGCTIMER (0x400FE000U + 0x604U)
#define TIMER0 (0x40030000U)
#define GPTMCTL(timer) (timer + 0x00CU)
#define GPTMCFG(timer) (timer + 0x000U)
#define GPTMTAMR(timer) (timer + 0x004U)
#define GPTMTAILR(timer) (timer + 0x028U)
#define GPTMRIS(timer) (timer + 0x01CU)
#define GPTMICR(timer) (timer + 0x024U)
#define GPTMTAPR(timer) (timer + 0x038U)

unsigned int volatile i = 0;
unsigned int const timeout = 5; /* 5 seconds */

int main()
{
  /* Provide module with a clock */
  *((unsigned int*) RCGCTIMER) |= 1;
  
  /* 1. Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared) before making
   any changes. */
  
  /* Disabled */
  *((unsigned int*) GPTMCTL(TIMER0)) = 0;
  
  /* 2. Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000.*/
  //*((unsigned int*) GPTMCFG(TIMER0)) = 0x00U;
  *((unsigned int*) GPTMCFG(TIMER0)) = 0x04U; // set to 16 bit timer

  /* 3. Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR):
   * a. Write a value of 0x1 for One-Shot mode.
   * b. Write a value of 0x2 for Periodic mode. */
  
  /* One shot timer mode = bit one set */
  // *((unsigned int*) GPTMTAMR(TIMER0)) |=  (1 << 0);
  
  /* Periodic timer */
   *((unsigned int*) GPTMTAMR(TIMER0)) |=  (1 << 1);
  
  /* 5. Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR).*/
  
  /* 16 MHz Clock => clock period = 1/16MHz = 62.5 nano seconds 62.5 x 10^-9 seconds
   * 1 sec = (1/16MHz * (65.5 x 10^9) = 62,500,000,000 
   * > 16 bits
   * use 8-bit prescaler = 250
   * 16MHz/250 = 64000Hz
   * 1/64000 = 15.625 milli seconds
   * 1/15.625(millisec) => 1 second approx = 64000
   */ 
  
  /* set to 1 second */
  *((unsigned int*) GPTMTAILR(TIMER0)) =  (64000-1)*1;
  
  *((unsigned int*) GPTMTAPR(TIMER0)) = 250-1;
  
  /* 7. Set the TnEN bit in the GPTMCTL register to enable the timer and start counting.*/
  
  /* Enabled */
  *((unsigned int*) GPTMCTL(TIMER0)) |= (1 << 0);

  /* 8. Poll the GPTMRIS register or wait for the interrupt to be generated (if enabled). In both cases,
   * the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear
   * Register (GPTMICR).*/
  *((unsigned int*) GPTMICR(TIMER0)) |= (1 << 0);
  
  
  for(i = 0; i<timeout ; i++)
  {
    while(!*((unsigned int*) GPTMRIS(TIMER0)) & (1<<0))
    {
      // waiting on timeout
    }
    *((unsigned int*) GPTMICR(TIMER0)) |= (1 << 0);
  }
  
    
  return 0;
}
