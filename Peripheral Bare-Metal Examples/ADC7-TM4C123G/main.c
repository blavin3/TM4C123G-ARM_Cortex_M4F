/* 
 * Reading Anaolg input from a poteniometer
 *
 * Pot connected to 3.3V, GND and PD0 (pin 61 of TM4C123G)
 *
 * ADC PD0 -> AIN7 pin 61
 *
 * Code tested by setting break point at start of while loop 
 *
 * Using watch view value of ADC can be observed when breakpoint 
 * triggered
 */

#define GPIODATA_D  (0x40007000U)
#define RCGCADC  (0x400FE000U+0x638U)
#define RCGCGPIO (0x400FE000U+0x608U)
#define GPIODIR (GPIODATA_D + 0x400U)
#define GPIOAFSEL (GPIODATA_D + 0x420U)
#define GPIODEN (GPIODATA_D + 0x51CU) 
#define GPIOAMSEL (GPIODATA_D + 0x528U) 

#define ADC0 (0x40038000U)
#define ADCACTSS (ADC0+0x00U)
#define ADCEMUX (ADC0+0x14U)
#define ADCSSMUX3 (ADC0+0x0A0U)
#define ADCSSCTL3 (ADC0+0x0A4U)
#define ADCSSFIFO3 (ADC0+0x0A8)

unsigned int ain7_val = 0;
int main()
{ 
    /*1. Enable the ADC clock using the RCGCADC register (see page 352).*/
    *((unsigned int*)RCGCADC) |= 1U << 0; 
    
    /*2. Enable the clock to the appropriate GPIO modules via the RCGCGPIO register (see page 340).
    To find out which GPIO ports to enable, refer to “Signal Description” on page 801. */
    *((unsigned int*)RCGCGPIO) |= 1U << 3; 
    //*((unsigned int*)GPIODIR) &= ~(1U << 0);
    
    /*3. Set the GPIO AFSEL bits for the ADC input pins (see page 671). To determine which GPIOs to
    configure, see Table 23-4 on page 1344.*/
    *((unsigned int*)GPIOAFSEL) |= 1U << 0;
    
    /*4. Configure the AINx signals to be analog inputs by clearing the corresponding DEN bit in the
    GPIO Digital Enable (GPIODEN) register (see page 682). */
    *((unsigned int*)GPIODEN) |= 1U << 0;
    
    /*5. Disable the analog isolation circuit for all ADC input pins that are to be used by writing a 1 to
    the appropriate bits of the GPIOAMSEL register (see page 687) in the associated GPIO block. */
    *((unsigned int*)GPIOAMSEL) |= 1U << 0;
    
    /******************************/
    
    /*1. Ensure that the sample sequencer is disabled by clearing the corresponding ASENn bit in the
    ADCACTSS register. Programming of the sample sequencers is allowed without having them
    enabled. Disabling the sequencer during programming prevents erroneous execution if a trigger
    event were to occur during the configuration process.*/
    *((unsigned int*) ADCACTSS) &= ~(1U << 3);
    // SS3 only samples from one pin rather than multiple pins
    
    /*2. Configure the trigger event for the sample sequencer in the ADCEMUX register.*/
    *((unsigned int*) ADCEMUX) |= (0xFU << 12); // continuely reads samples no trigger needed
    
    /*4. For each sample in the sample sequence, configure the corresponding input source in the
    ADCSSMUXn register.*/
    *((unsigned int*) ADCSSMUX3) |= (0x07U << 0); //using ain7 set ssmux3 to 7
    
    /*5. For each sample in the sample sequence, configure the sample control bits in the corresponding
    nibble in the ADCSSCTLn register. When programming the last nibble, ensure that the END bit
    is set. Failure to set the END bit causes unpredictable behavior.*/
    *((unsigned int*) ADCSSCTL3) |= (0x01U << 1);
        
    /*7. Enable the sample sequencer logic by setting the corresponding ASENn bit in the ADCACTSS
    register. */
    *((unsigned int*) ADCACTSS) |= (0x01U << 3); 
        
    while(1)
    {
      ain7_val = *((unsigned int*) ADCSSFIFO3); // bits 0-11 (12 bit ADC);
    }
    
  //return 0;
}