
#define F_CPU 16000000
#define CHECKBIT(x,y) (x & (y))
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
volatile long cnt;
//-----------------------------------serial----------------------------------------
void serial_init(void) 
{
  unsigned int baudrate[15] ={416,207,103,68,51,34,25,16,12,8,3,3,1,0};
 


  UBRR1L = baudrate[2]; 
  UBRR1H = baudrate[2]>>8;      
  
  UBRR0L = baudrate[2];
  UBRR0H = baudrate[2]>>8;               // 4:19200bps; 6:38400; 7:57600; 8:76800; 9;115200
  


  
  UCSR1C = (1 << UCSZ1) | (1 << UCSZ0);  // no parity ,  stop bit 1 , data 8
 UCSR1B = (1 << TXEN1) | (1 << RXEN1);
  // UCSR1A = (1 << U2X0);                //double baudrate 
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

unsigned int Rxdata1 (void)
{

	// Wait for empty transmit buffer 
	while ( !(UCSR1A & (1<<RXC1)) );

	// Receive data from buffer, return the data 
	return UDR1;	

}

void transmit1(unsigned char data)
{
while(!(UCSR1A & (1<<UDRE1)));
UDR1=data;

}

unsigned int send_code_portD(char data)
{
	unsigned char bit_to_check=0x80;
	unsigned int flag=0,cnt1=0;
	while(flag<8)
	{
			
		if (!(CHECKBIT(data, bit_to_check)))
		{
			bit_to_check = bit_to_check >> 1;
			if(!(CHECKBIT(data, bit_to_check)))
			{
				PORTD= 0x07;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}
				//PORTD= 0x07;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}
				PORTD= 0x00;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}
			}
			else
			{
				PORTD= 0x00;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}
				PORTD= 0x07;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}
				
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}
				//PORTD= 0x07;
				PORTD= 0x00;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}
				
			}
		//	PORTD= 0x00;
		}
		else
		{	
			bit_to_check = bit_to_check >> 1;
			if(!(CHECKBIT(data, bit_to_check)))
			{
				PORTD= 0x00;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}

			//	PORTD= 0x00;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}

				PORTD= 0x07;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}

			
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}
				PORTD= 0x00;

			}

			else
			{
				PORTD= 0x07;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}

				PORTD= 0x00;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}

				PORTD= 0x07;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}
				PORTD= 0x00;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}
			//	PORTD= 0x00;
			}
		}
		flag=flag+2;
		bit_to_check = bit_to_check >> 1;
//		_delay_us(50);
/*	cnt1 = 0, cnt=0;
		while(cnt1==0)
		{
			cnt1 = cnt;
		}
	}*/
	}
	return 1;
}


unsigned int send_code_portB(char data)
{
	unsigned char bit_to_check=0x80;
	unsigned int flag=0,cnt1=0;
	while(flag<8)
	{
			
		if (!(CHECKBIT(data, bit_to_check)))
		{
			bit_to_check = bit_to_check >> 1;
			if(!(CHECKBIT(data, bit_to_check)))
			{
				PORTB= 0x07;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}
				//PORTD= 0x07;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}
				PORTB= 0x00;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}
			}
			else
			{
				PORTB= 0x00;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}
				PORTB= 0x07;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}
				
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}
				//PORTD= 0x07;
				PORTB= 0x00;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}
				
			}
		//	PORTD= 0x00;
		}
		else
		{	
			bit_to_check = bit_to_check >> 1;
			if(!(CHECKBIT(data, bit_to_check)))
			{
				PORTB= 0x00;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}

			//	PORTD= 0x00;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}

				PORTB= 0x07;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}

			
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}
				PORTB= 0x00;

			}

			else
			{
				PORTB= 0x07;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}

				PORTB= 0x00;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}

				PORTB= 0x07;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}
				PORTB= 0x00;
				cnt1 =0, cnt = 0;
				while(cnt1 == 0)
				{
					cnt1 = cnt;
				}
			//	PORTD= 0x00;
			}
		}
		flag=flag+2;
		bit_to_check = bit_to_check >> 1;
//		_delay_us(50);
/*	cnt1 = 0, cnt=0;
		while(cnt1==0)
		{
			cnt1 = cnt;
		}
	}*/
	}
	return 1;
}



unsigned int new_data_send(char data)
{
	int cnt1=0;
	
	PORTD = 0x07;
	cnt1 = 0, cnt=0;
	while(cnt1==0)
	{
		cnt1 = cnt;
	}
	PORTD = 0x00;
	
}

unsigned int end_break()
{
	int cnt1=0,i;
	
	PORTD = 0x00;
	for(i=0;i<16;i++)
	{
	cnt1 = 0, cnt=0;
	while(cnt1==0)
	{
		cnt1 = cnt;
	}
	}
	PORTD = 0x00;
	return 0;
}


unsigned int end_breakB()
{
	int cnt1=0,i;
	
	PORTD = 0x00;
	for(i=0;i<16;i++)
	{
	cnt1 = 0, cnt=0;
	while(cnt1==0)
	{
		cnt1 = cnt;
	}
	}
	PORTD = 0x00;
	return 0;
	
}



//-----------------------------------main----------------------------------------




int main(void)
{   
	unsigned int ctr,i=0,cnt1=0;
	unsigned char Rd[32],Rd1[32],data[10]={0,1,2,3,4,5,6,7,8,9};
	serial_init();
	Timer1_init();
	DDRA=0xFF;
	DDRD=0xFF;
	DDRB=0xFF;
	TIMSK |= 0x04;
	SREG |= 0x80;
	PORTA = 0x01;
    while(1)
    {
		
	
		send_code_portD(0xFF);
		send_code_portD(0x01);
		send_code_portD(0x02);
		send_code_portD(0x03);
		send_code_portD(0x04);
		send_code_portD(0x05);
		send_code_portD(0x06);
		send_code_portD(0x07);
		send_code_portD(0x08);
		send_code_portD(0x09);
		end_break();
		/*send_code_portB(0xFF);
		send_code_portB(0x11);
		send_code_portB(0x12);
		send_code_portB(0x13);
		send_code_portB(0x14);
		send_code_portB(0x15);
		send_code_portB(0x16);
		send_code_portB(0x17);
		send_code_portB(0x18);
		send_code_portB(0x19);
		end_breakB();*/
	
		PORTA ^= 0x01;
	
  	}	


}

