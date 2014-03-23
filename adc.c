#include <msp430.h>
#include <CBuf/cbuf.h>

static uintCircularBuffer adcBuffer;

void configureADC(void)
{
  ADC10CTL1 = INCH_3 + ADC10DIV_3 ;         // Channel 3, ADC10CLK/3
  ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON + ADC10IE;  // Vcc & Vss as reference, Sample and hold for 64 Clock cycles, ADC on, ADC interrupt enable
  ADC10AE0 |= BIT3;                         // ADC input enable P1.3
  ADC10CTL0 |= ENC | ADC10SC; /** Fight! */
}

unsigned char ADCAvailable(void){
  return uintAvailable(&adcBuffer);
}

unsigned int ADCnext(void){
  return uintPop(&adcBuffer);
}

/* ADC10 interrupt service routine */
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
  unsigned int ADC_value;
  ADC10CTL0 |= ENC + ADC10SC;            // Sampling and conversion start
  ADC_value = ADC10MEM;                // Assigns the value held in ADC10MEM to the integer called ADC_value
  uintPush(ADC_value, &adcBuffer);
}
