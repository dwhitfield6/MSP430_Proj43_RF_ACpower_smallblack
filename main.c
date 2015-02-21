

#include <msp430.h>				

#define TX BIT0
#define AC1 BIT6
#define AC2 BIT7

void send_rf(unsigned char, unsigned char*);
void zero(unsigned char);
void one(unsigned char);
void f(unsigned char);

//unsigned char TXdata[12] = {0,2,2,2,2,2,0,0,1,0,0,0}; //channel E
unsigned char TXdata[12] = {2,2,2,2,2,2,0,0,1,0,0,0}; //channel D
unsigned char ON =0;
unsigned char oldON =0;
unsigned char ii=0;
int ONCount =0;
int ledcount =0;


int main(void) {
	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
	  P1DIR |= TX;// Set all pins but RXD to output
	  P1OUT &= ~TX;// Set all pins but RXD to output

	  __enable_interrupt(); // enable all interrupts                                   // Enable CPU interrupts
	while(1)
	{
		ONCount=0;
		for(ii=10;ii>0;ii--)
		             {
		           	    if((P1IN & AC1) == AC1)
		           	    {
		           	    	ONCount++;
		           	    }
		           	    _delay_cycles(10);
		             }

		        if(ONCount >8)
		        {
		        ON = 1;
		        }
		        else
		        {
		        	ON =0;
		        }


       if(oldON != ON)
       {
      		send_rf(TX, TXdata);
      		send_rf(TX, TXdata);
      		send_rf(TX, TXdata);
      		send_rf(TX, TXdata);

          		_delay_cycles(100000);

       }
           		oldON = ON;
	}
}

void send_rf(unsigned char pin, unsigned char* data)
{
unsigned char i=0;

for(i=0;i<12;i++)
{
if(data[i] == 0)
{
	zero(pin);
}
else if(data[i] ==1)
{
	one(pin);
}
else
{
	f(pin);
}

}

P1OUT |= pin;
_delay_cycles(250);
P1OUT &= ~pin;
_delay_cycles(7000);
}

void zero(unsigned char pin)
{
	P1OUT |= pin;
	_delay_cycles(250);
	P1OUT &= ~pin;
	_delay_cycles(690);
	P1OUT |= pin;
	_delay_cycles(250);
	P1OUT &= ~pin;
	_delay_cycles(690);
}
void one(unsigned char pin)
{
	P1OUT |= pin;
	_delay_cycles(810);
	P1OUT &= ~pin;
	_delay_cycles(210);
	P1OUT |= pin;
	_delay_cycles(810);
	P1OUT &= ~pin;
	_delay_cycles(210);
}
void f(unsigned char pin)
{
	P1OUT |= pin;
	_delay_cycles(250);
	P1OUT &= ~pin;
	_delay_cycles(700);
	P1OUT |= pin;
	_delay_cycles(810);
	P1OUT &= ~pin;
	_delay_cycles(200);
}

