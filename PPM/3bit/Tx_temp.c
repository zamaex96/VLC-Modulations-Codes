
/*
	-----------------------------------
	Author: Sejan Mohammad Abrar Shakil
	Code: Pulse position modulation
	MIMO uisng port C Atmega128
	-----------------------------------
*/
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
	cycles = 120;	// 2/(16000000/64)*125 = 1ms , *25 = 0.2ms
	ICR1 = cycles;
	//sei();
	SREG = oldSREG;

	
	TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12));
	TCCR1B |= (1 << CS11) ;	// prescale: clk / 8
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



 unsigned int delay_in_signal(int i){
 	
	int k=0,cnt1=0;
 	for(k =0;k<i;k++)
	{
		cnt1 = 0, cnt=0;
		while(cnt1==0)
		{
			cnt1 = cnt;
		}
	}
 }


// Sending data using port C

unsigned int send_code_portC(char data)
{
	unsigned char bit_to_check=0x80;
	unsigned int flag=0,cnt1=0,k=0,i=0,j=7;
	while(flag<8)
	{
		if(i > 0)
		{
			delay_in_signal(i);
		}
			
		if (!(CHECKBIT(data, bit_to_check)))
		{
			PORTC= 0x07;
		}
		else
		{	
			PORTC = 0x00;
		}
		flag++;
		bit_to_check = bit_to_check >> 1;
//		_delay_us(50);
		cnt1 = 0, cnt=0;
		while(cnt1==0)
		{
			cnt1 = cnt;
		}
		PORTC = 0x07;
		if(j>0)
		{
			delay_in_signal(j);
		}
		i++;
		j--;
	}
	

	return 1;
}







//Sendign signal using PPM modulation



unsigned int ppm_test(char data){

	unsigned char bit_to_check=0x80;
	int k=0, cnt1=0;
	

}


unsigned int send_data_ppm(char data)
{
	unsigned char bit_to_check=0x80;
	unsigned char bit_to_check_2=0x08;
	int k=0, cnt1=0;
//	for(k=0;k<4;k++)
//	{
		if (!(CHECKBIT(data, bit_to_check)))
		{
			PORTC= 0x00;
		}
		else
		{	
			PORTC = 0x07;
		}

		cnt1 = 0, cnt=0;
		while(cnt1==0)
		{
			cnt1 = cnt;
		}
		PORTC= 0x00;
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
		bit_to_check = bit_to_check >> 1;
		cnt1 = 0, cnt=0;
		while(cnt1==0)
		{
			cnt1 = cnt;
		}
		if (!(CHECKBIT(data, bit_to_check)))
		{
			PORTC= 0x00;
		}
		else
		{	
			PORTC = 0x07;
		}
		cnt1 = 0, cnt=0;
		while(cnt1==0)
		{
			cnt1 = cnt;
		}
		PORTC = 0x00;
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
		bit_to_check = bit_to_check >> 1;
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
		while(cnt1==0)
		{
			cnt1 = cnt;
		}
		if (!(CHECKBIT(data, bit_to_check)))
		{
			PORTC= 0x00;
		}
		else
		{	
			PORTC = 0x07;
		}
		cnt1 = 0, cnt=0;
		while(cnt1==0)
		{
			cnt1 = cnt;
		}
		PORTC = 0x00;
		cnt1 = 0, cnt=0;
		while(cnt1==0)
		{
			cnt1 = cnt;
		}

		bit_to_check = bit_to_check >> 1;
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
		if (!(CHECKBIT(data, bit_to_check)))
		{
			PORTC= 0x00;
		}
		else
		{	
			PORTC = 0x07;
		}
		cnt1 = 0, cnt=0;
		while(cnt1==0)
		{
			cnt1 = cnt;
		}
		PORTC = 0x00; // Here First half ends


		
//	}
	
}

unsigned int header()
{
	unsigned char bit_to_check=0x80;
	unsigned int flag=0,cnt1=0,data[10],c=0,n=0,m=0,x=0,y=0,z=0,k=0;

		PORTC = 0x07;	//000
		for(n=0;n<4;n++)
		{
		cnt1 = 0, cnt=0;
			while(cnt1==0)
			{
				cnt1 = cnt;
			}
		}
		PORTC = 0x00;
		for(n=0;n<4;n++)
		{
			cnt1 = 0, cnt=0;
			while(cnt1==0)
			{
				cnt1 = cnt;
			}
		}
}


unsigned int end()
{
	unsigned char bit_to_check=0x80;
	unsigned int flag=0,cnt1=0,data[10],c=0,n=0,m=0,x=0,y=0,z=0,k=0;

		PORTC = 0x00;
		for(n=0;n<4;n++)
		{
			cnt1 = 0, cnt=0;
			while(cnt1==0)
			{
				cnt1 = cnt;
			}
		}
} 

unsigned int ppm_mod(char data1)
{
	unsigned char bit_to_check=0x80;
	unsigned int flag=0,cnt1=0,data[10],c=0,n=0,m=0,x=0,y=0,z=0,k=0;
	
	while(flag<8)
	{
		if (!(CHECKBIT(data1, bit_to_check)))
		{
			data[flag] = 0;
		}
		else
		{	
			data[flag] = 1;
		}
		flag++;
		bit_to_check = bit_to_check >> 1;
	}
	
	data[8]=0;
	
	for(k=0;k<3;k++)
	{
		if( data[m] ==0)
		{
			if(data[m+1]==0)	
			{
				if( data[m+2]==0)
				{
					PORTC = 0x07;	//000
					cnt1 = 0, cnt=0;
						while(cnt1==0)
						{
							cnt1 = cnt;
						}
					PORTC = 0x00;
					for(n=0;n<7;n++)
					{
						cnt1 = 0, cnt=0;
						while(cnt1==0)
						{
							cnt1 = cnt;
						}
					}
				}
				else	//001
				{
					cnt1 = 0, cnt=0;
						while(cnt1==0)
						{
							cnt1 = cnt;
						}
					PORTC = 0x07;
						cnt1 = 0, cnt=0;
						while(cnt1==0)
						{
							cnt1 = cnt;
						}
					PORTC = 0x00;
					for(n=0;n<6;n++)
					{
						cnt1 = 0, cnt=0;
						while(cnt1==0)
						{
							cnt1 = cnt;
						}
					}
				}
			}
			else
			{
				if( data[m+2]==0)
				{
					//010
					for(n=0;n<2;n++)
					{
					cnt1 = 0, cnt=0;
						while(cnt1==0)
						{
							cnt1 = cnt;
						}
					}
					PORTC = 0x07;
					cnt1 = 0, cnt=0;
						while(cnt1==0)
						{
							cnt1 = cnt;
						}
					PORTC = 0x00;
					for(n=0;n<5;n++)
					{
						cnt1 = 0, cnt=0;
						while(cnt1==0)
						{
							cnt1 = cnt;
						}
					}
				}
				else	//001
				{
						//011
					
					for(n=0;n<3;n++)
					{
					cnt1 = 0, cnt=0;
						while(cnt1==0)
						{
							cnt1 = cnt;
						}
					}
					PORTC = 0x07;
					cnt1 = 0, cnt=0;
						while(cnt1==0)
						{
							cnt1 = cnt;
						}
					PORTC = 0x00;
					for(n=0;n<4;n++)
					{
						cnt1 = 0, cnt=0;
						while(cnt1==0)
						{
							cnt1 = cnt;
						}
					}
				}
			}
		}
		else
		{
			if(data[m+1]==0)	
			{
				if( data[m+2]==0)
				{
					//100
					for(n=0;n<4;n++)
					{
					cnt1 = 0, cnt=0;
						while(cnt1==0)
						{
							cnt1 = cnt;
						}
					}
					PORTC = 0x07;
					cnt1 = 0, cnt=0;
						while(cnt1==0)
						{
							cnt1 = cnt;
						}
					PORTC = 0x00;
					for(n=0;n<3;n++)
					{
						cnt1 = 0, cnt=0;
						while(cnt1==0)
						{
							cnt1 = cnt;
						}
					}
				}
				else
				{
						//101
					for(n=0;n<5;n++)
					{
					cnt1 = 0, cnt=0;
						while(cnt1==0)
						{
							cnt1 = cnt;
						}
					}
					PORTC = 0x07;
					cnt1 = 0, cnt=0;
						while(cnt1==0)
						{
							cnt1 = cnt;
						}
					PORTC = 0x00;
					for(n=0;n<2;n++)
					{
						cnt1 = 0, cnt=0;
						while(cnt1==0)
						{
							cnt1 = cnt;
						}
					}
				}
			}
			else
			{
				if( data[m+2]==0)
				{
						//110
					for(n=0;n<6;n++)
					{
					cnt1 = 0, cnt=0;
						while(cnt1==0)
						{
							cnt1 = cnt;
						}
					}
					PORTC = 0x07;
					cnt1 = 0, cnt=0;
						while(cnt1==0)
						{
							cnt1 = cnt;
						}
					PORTC = 0x00;
					for(n=0;n<1;n++)
					{
						cnt1 = 0, cnt=0;
						while(cnt1==0)
						{
							cnt1 = cnt;
						}
					}
				}
				else
				{
						//111
					for(n=0;n<7;n++)
					{
					cnt1 = 0, cnt=0;
						while(cnt1==0)
						{
							cnt1 = cnt;
						}
					}
					PORTC = 0x07;
						cnt1 = 0, cnt=0;
						while(cnt1==0)
						{
							cnt1 = cnt;
						}
					PORTC = 0x00;
					
				}
			}
		}

		m = m+3;
	}


	


}


// Sending data using port D

unsigned int send_code_portD(char data)
{
	unsigned char bit_to_check=0x80;
	unsigned int flag=0,cnt1=0;
	while(flag<8)
	{
			
		if (!(CHECKBIT(data, bit_to_check)))
		{
			PORTD= 0x00;
		}
		else
		{	
			PORTD = 0x07;
		}
		flag++;
		bit_to_check = bit_to_check >> 1;
//		_delay_us(50);
	cnt1 = 0, cnt=0;
		while(cnt1==0)
		{
			cnt1 = cnt;
		}
	}
	return 1;
}






//-----------------------------------main----------------------------------------




int main(void)
{   
	unsigned int ctr;
	unsigned char Rd[32],Rd1[32];
	serial_init();
	Timer1_init();
	DDRA=0xFF;
	DDRD=0xFF;
	DDRC = 0xFF;
	TIMSK |= 0x04;
	SREG |= 0x80;
//	PORTA = 0x01;
    while(1)
    {
	
		//for(ctr=0; ctr <1420; ctr = ctr + 2)
		// Frame: FF | 80 | PM2.5(MSB)(6) | PM2.5(LSB) (7)| PM10(MSB) (8)| PM10(LSB) (9)| 0x00

	/*	transmit0(0x42);
		transmit0(0x4d);
		transmit0(0xe2);
		transmit0(0x00);
		transmit0(0x00);
		transmit0(0xFF);
		transmit0(0xFF);

		for(ctr=0; ctr <32; ctr++)
		{
					

			Rd[ctr] = Rxdata();
		
		}


		transmit1(0x42);
		transmit1(0x4d);
		transmit1(0xe2);
		transmit1(0x00);
		transmit1(0x00);
		transmit1(0xFF);
		transmit1(0xFF);

		for(ctr=0; ctr <32; ctr++)
		{
					

			Rd1[ctr] = Rxdata1();
		
		}*/
		
	//	transmit1(0xFF);
	//	transmit1(0x80);
	/*	for(ctr=0; ctr <32; ctr++)
		{
			
			transmit1(Rd[ctr]);
		
		}*/
	//	transmit1(Rd[6]);
	//	transmit1(Rd[7]);
	//	transmit1(Rd[8]);
	//	transmit1(Rd[9]);
	//	transmit1(0x00);
	//	send_code_portC(0xFF);
	//	send_code_portC(0x80);
		header();
		ppm_mod(0x29);
		ppm_mod(0x45);
		end();
		//ppm_mod(0x10);
		//ppm_mod(0x20);
		//ppm_mod(0x25);
		//ppm_mod(0x00);
	//	ppm_mod(0xE3);
	//	_delay_ms(1);
	//	ppm_mod(0xAF);
	//	send_data_ppm(0xD5);
		
		/*send_code_portD(0xFF);
		send_code_portD(0x80);
		send_code_portD(0x11);
		send_code_portD(0x12);
		send_code_portD(0x13);
		send_code_portD(0x14);
		send_code_portD(0x00);

		send_code_portC(0xFF);
		send_code_portC(0x80);
		send_code_portC(0x21);
		send_code_portC(0x22);
		send_code_portC(0x23);
		send_code_portC(0x24);
		send_code_portC(0x00);*/
	//	_delay_ms(100);

		PORTA ^= 0x01;
	
  	}	

}

