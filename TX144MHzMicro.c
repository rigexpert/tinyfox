/*****************************************************
Project : TX144MHzMicro
Version : 1
Date    : 30.11.2017
Author  : UT5UML
Company : REU
Comments: 


Chip type               : ATtiny10
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Tiny
External RAM size       : 0
Data Stack size         : 8
*****************************************************/

#include <tiny10.h>

#define PERIOD 250 
unsigned int  i=0; // counter
unsigned char k=0; // counter

typedef struct FoxSignal
{
   unsigned char Slot;
   unsigned char Val;
} FoxSignal;


flash FoxSignal CW[] = {
{3,1},
{1,0},
{3,1},
{3,0},
{3,1},
{1,0},
{3,1},
{1,0},
{3,1},
{3,0},
{1,1},
{1,0},//1
{1,1},
{1,0},//2
{1,1},
{1,0},//3
{1,1},
{1,0},//4
{1,1},
{1,0},
{1,0},
{1,0},
{0,0}
};

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
// Reinitialize Timer 0 value
TCNT0=0xF060;
//TCNT0=0xFFC0; //128 kHz
// Place your code here
//         DDRB |= 0x07; // Set pins 1,2 as output
//         PORTB = 0x04;

if (i)
    {
     i--;
     if(CW[k].Val==0)
        { 
         DDRB  = 0x00; // Set pins  as input
         PORTB = 0;
        }
     else
        {
         DDRB |= 0x06; // Set pins 1,2 as output
         PORTB |= 0x04; 
         
         DDRB ^= 0x01; // invert pin 0  input/output
         
        }
           
     
     
    }
    
else
    { 
     k++;
     if(CW[k].Slot==0) k=0;
     i =((unsigned int)(CW[k].Slot))*PERIOD;
    } 
    
}

// Declare your global variables here

void main(void)
{
// Declare your local variables here

// Clock Prescaler division factor: 1
#pragma optsize-
CCP=0xD8;
CLKPSR=0x00;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif
//CLKMSR=0x01; //128 kHz

// Voltage Level Monitor
// Trigger Level: 1.6V -> Power-On Reset
// Interrupt: Off
VLMCSR=0x01;

// Input/Output Ports initialization
// Port B initialization
PUEB=0x00;
// Break Before Make Mode: Off
PORTCR=0x00;
// Func3=In Func2=Out Func1=In Func0=In 
// State3=T State2=0 State1=T State0=T 
PORTB=0x00;
DDRB=0x04;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 8000.000 kHz
// Mode: Normal top=FFFFh
// Input Capture on Falling Edge
// Input Capture Noise Canceler: Off
// OC0A output: Disconnected
// OC0B output: Disconnected
TCCR0A=0x00;
TCCR0B=0x01;
TCNT0=0xF060; // 8 MHz
//TCNT0=0xFFC0; //128 kHz
ICR0=0x0000;
OCR0A=0x0000;
OCR0B=0x0000;

// External Interrupt(s) initialization
// INT0: Off
// Interrupt on any change on pins PCINT0-3: Off
EICRA=0x00;
EIMSK=0x00;
PCICR=0x00;

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=0x01;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 0: Off
ACSR=0x80;

// Global enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here

      };
}
