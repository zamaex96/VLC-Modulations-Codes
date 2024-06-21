#define F_CPU 16000000
#define CHECKBIT(x,y) (x & (y))
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
unsigned char data[32];
volatile long cnt;

//-----------------------------------serial----------------------------------------
void serial_init(void) 
{
  unsigned int baudrate[15] ={416,207,103,68,51,34,25,16,12,8,3,3,1,0}; 

  UBRR1L = baudrate[9];
  UBRR1H = baudrate[9]>>8;      
  
  UBRR0L = baudrate[2];
  UBRR0H = baudrate[2]>>8;         
   
  UCSR1C = (1 << UCSZ1) | (1 << UCSZ0);  // no parity ,  stop bit 1 , data 8
  UCSR1B = (1 << TXEN) | (1 << RXEN);
  //double baudrate 
  UCSR0C = (1 << UCSZ1) | (1 << UCSZ0);  //serial 8-bit format. no parity, stop bit 1, data 8
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);    //enable tx rx located in control reg UCSR1B
                                         //When set, these two bits turn on the serial buffers to allow for serial communications
}


void Timer1_init(void) 
{

	//unsigned int cycles;
	unsigned long cycles;
  	// Initializing Timer
	TCCR1A = 0;                 // clear control register A 
	TCCR1B |= (1 << WGM13); // set mode 8: phase and frequency correct pwm, stop the timer
 	
	unsigned char oldSREG = SREG;
	cli();

	//cycles = 20; // 2/(16000000/8)*10 = 10us, *20 = 20us (50KHz)
	cycles = 50;	// 2/(16000000/64)*125 = 1ms , *25 = 0.2ms
	ICR1 = cycles;
	//sei();
	SREG = oldSREG;

	
	TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12));
	TCCR1B |= (1 << CS11);	// prescale: clk / 8
	//TCCR1B |= (1 << CS12);	// prescale: clk / 256
	//TCCR1B |= (1 << CS11) | (1 << CS10);	// prescale: clk / 64
	//TCCR1B |= (1 << CS11) | (1 << CS10);	// prescale: clk / 64

	

}

ISR(TIMER1_OVF_vect)
{
	cnt++;
}



void transmit1(unsigned char data)
{
while(!(UCSR1A & (1<<UDRE1)));
UDR1=data;

}

void transmit0(unsigned char data)
{
while(!(UCSR0A & (1<<UDRE0)));
UDR0=data;

}

unsigned int Rxdata (void)
{

	// Wait for empty transmit buffer 
	while ( !(UCSR0A & (1<<RXC0)) );

	// Receive data from buffer, return the data 
	return UDR0;	

}



// Send Data using pulse wide modulation
// 00 is one time, 01 is two times, 10 is three times and 11 is four times

unsigned int pwm_test(char data)
{
	unsigned char bit_to_check=0x80;
	unsigned int flag=0,cnt1=0;
	while(flag<4)
	{
		if ((CHECKBIT(data, bit_to_check)))
		{
			PORTA = 0x00;
			bit_to_check = bit_to_check >> 1;
			if((CHECKBIT(data, bit_to_check)))
			{
				PORTA = 0x07;
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				PORTA = 0x00;
			}
			else
			{
				PORTA = 0x07;
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				PORTA = 0x00;
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
			}
		}

		else
		{
			bit_to_check = bit_to_check >> 1;
			if((CHECKBIT(data, bit_to_check)))
			{
				PORTA = 0x07;	
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				PORTA = 0x00;
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
			}
			else
			{
				PORTA = 0x07;			
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				PORTA = 0x00;
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
			}
		}
		bit_to_check = bit_to_check >> 1;
		flag++;
	}
}


unsigned int pwm_test_B(char data)
{
	unsigned char bit_to_check=0x80;
	unsigned int flag=0,cnt1=0;
	while(flag<4)
	{
		if ((CHECKBIT(data, bit_to_check)))
		{
			PORTB = 0x00;
			bit_to_check = bit_to_check >> 1;
			if((CHECKBIT(data, bit_to_check)))
			{
				PORTB = 0x07;
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				PORTB = 0x00;
			}
			else
			{
				PORTB = 0x07;
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				PORTB = 0x00;
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
			}
		}

		else
		{
			bit_to_check = bit_to_check >> 1;
			if((CHECKBIT(data, bit_to_check)))
			{
				PORTB = 0x07;	
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				PORTB = 0x00;
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
			}
			else
			{
				PORTB = 0x07;			
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				PORTB = 0x00;
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
				cnt1 = 0, cnt=0;
				while(cnt1==0)
				{
					cnt1 = cnt;
				}
			}
		}
		bit_to_check = bit_to_check >> 1;
		flag++;
	}
}


unsigned int end_space(){
	
	unsigned int i=0,cnt1=0;
	for(i=0;i<8;i++)
	{
		PORTA = 0x00;
		cnt1 = 0, cnt=0;
		while(cnt1==0)
		{
			cnt1 = cnt;
		}
	}
}

//-------------------------------PM Sensor Data -----------------------------


unsigned int getSensorData(){
		
	unsigned int ctr;
	

	transmit0(0x42);
	transmit0(0x4d);
	transmit0(0xe2);
	transmit0(0x00);
	transmit0(0x00);
	transmit0(0x00);
	transmit0(0x00);

	for(ctr=0; ctr <32; ctr++)
		{
					

			data[ctr] = Rxdata();
		
		}

	return data;

}

//Main Function----------------------------------------------------------------------------

int main(void)
{   
	serial_init();
	Timer1_init();
	DDRD=0xFF;
	DDRB=0xFF;
	TIMSK |= 0x04;
	SREG |= 0x80;
	DDRA=0xFF;		//sets portA pins as output 
	DDRC=0xFF;
	DDRF=0xFF;
	while(1){


//		getSensorData();

		pwm_test(0x1B);
		pwm_test(0x15);
		pwm_test(0x25);
		pwm_test(0x35);
		pwm_test(0x45);
		end_space();
/*
		pwm_test_B(0x1B);
		pwm_test_B(0x55);
		pwm_test_B(0x65);
		pwm_test_B(0x75);
		pwm_test_B(0x85);
		end_space();*/
		
	
	PORTA ^= 0x01;
	}

}
