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

  UBRR1L = baudrate[9];
  UBRR1H = baudrate[9]>>8;      
  
  UBRR0L = baudrate[9];
  UBRR0H = baudrate[9]>>8;         
   
  UCSR1C = (1 << UCSZ1) | (1 << UCSZ0);  // no parity ,  stop bit 1 , data 8
  UCSR1B = (1 << TXEN) | (1 << RXEN);
  //double baudrate 
  UCSR0C = (1 << UCSZ1) | (1 << UCSZ0);  //serial 8-bit format. no parity, stop bit 1, data 8
  UCSR0B = (1 << TXEN) | (1 << RXEN);    //enable tx rx located in control reg UCSR1B
                                         //When set, these two bits turn on the serial buffers to allow for serial communications
}

void transmit(unsigned char data)
{
while(!(UCSR1A & (1<<UDRE1)));
UDR1=data;

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
//---------------------------------------------------Header Synchronization----------------------------------------------



unsigned int pwm_sync()
{
	unsigned int temp;
	unsigned int byte_placeholder;
	unsigned int byte_placeholder1;
	unsigned int bit_to_check;
	unsigned int bit_to_shift;
	unsigned int predata,cnt1=0,data[20],i;
	int flag 			= 0;
	bit_to_check 		= 0x01;
	byte_placeholder	= 0x00;
	byte_placeholder1	= 0xFF80;
	predata				= 0x00;
	temp = PINA;
	while(!(CHECKBIT(temp, bit_to_check))){temp = PINA; }//transmit(0x88);}

	while(1)
	{
		temp = PINA;	
		if(CHECKBIT(temp, bit_to_check)){
			
				bit_to_shift = 0x01;				
				byte_placeholder = byte_placeholder<<1;
				byte_placeholder = byte_placeholder|bit_to_shift;			
			}	
		else
			{
				bit_to_shift = 0x00;				
				byte_placeholder = byte_placeholder<<1;
				byte_placeholder = byte_placeholder|bit_to_shift;	
			}
		if(byte_placeholder == 0x8CEF)
		break;
		cnt1 = 0, cnt=0;
		while(cnt1==0)
		{
			cnt1 = cnt;
		}
		//transmit(byte_placeholder);
	}
}

unsigned int pwm_sync_B()
{
	unsigned int temp;
	unsigned int byte_placeholder;
	unsigned int byte_placeholder1;
	unsigned int bit_to_check;
	unsigned int bit_to_shift;
	unsigned int predata,cnt1=0,data[20],i;
	int flag 			= 0;
	bit_to_check 		= 0x01;
	byte_placeholder	= 0x00;
	byte_placeholder1	= 0xFF80;
	predata				= 0x00;
	temp = PINB;
	while(!(CHECKBIT(temp, bit_to_check))){temp = PINA; }//transmit(0x88);}

	while(1)
	{
		temp = PINB;	
		if(CHECKBIT(temp, bit_to_check)){
			
				bit_to_shift = 0x01;				
				byte_placeholder = byte_placeholder<<1;
				byte_placeholder = byte_placeholder|bit_to_shift;			
			}	
		else
			{
				bit_to_shift = 0x00;				
				byte_placeholder = byte_placeholder<<1;
				byte_placeholder = byte_placeholder|bit_to_shift;	
			}
		if(byte_placeholder == 0x8CEF)
		break;
		cnt1 = 0, cnt=0;
		while(cnt1==0)
		{
			cnt1 = cnt;
		}
		//transmit(byte_placeholder);
	}
}


// --------------------------- Data Detection ----------------------------------

unsigned int get_position(int i,int j, int k,int m)
{
	if(i==1 && j==0 && k==0 && m==0)
	{
		return 0;
	}
	else if(i==1 && j==1 && k==0 && m==0)
	{
		return 1;
	}
	else if(i==1 && j==1 && k==1 && m==0)
	{
		return 2;
	}
	else if(i==1 && j==1 && k==1 && m==1)
	{
		return 3;
	}
}


unsigned int pwm_data_3()
{
	unsigned int temp;
	unsigned int byte_placeholder;
	unsigned int byte_placeholder1;
	unsigned int bit_to_check;
	unsigned int bit_to_shift,p1=0,p2=0,p3=0,p4=0;
	unsigned int predata,cnt1=0,data[20],i;
	int flag 			= 0;
	bit_to_check 		= 0x01;
	byte_placeholder	= 0x00;
	byte_placeholder1	= 0xFF80;
	predata				= 0x00;

	for(i=0;i<16;i++)
	{
		cnt1 = 0, cnt=0;
		while(cnt1==0)
		{
			cnt1 = cnt;
		}
		temp = PINA;
		if(CHECKBIT(temp, bit_to_check)){
			data[i] = 1;			
			}	
		else
			{
				data[i] =0;	
			}
		
		//flag++;
	}

	p1 = get_position(data[0],data[1],data[2],data[3]);
	p2 = get_position(data[4],data[5],data[6],data[7]);
	p3 = get_position(data[8],data[9],data[10],data[11]);
	p4 = get_position(data[12],data[13],data[14],data[15]);
	
	if(p1 == 0)
	{
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if (p1 == 1)
	{
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if(p1 == 2)
	{
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if(p1 ==3)
	{
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	if(p2 == 0)
	{
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if (p2 == 1)
	{
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if(p2 == 2)
	{
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if(p2==3)
	{
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	if(p3 == 0)
	{
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if (p3 == 1)
	{
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if(p3 == 2)
	{
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if(p3==3)
	{
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	if(p4 == 0)
	{
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if (p4 == 1)
	{
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if(p4 == 2)
	{
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if(p4 == 3)
	{
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	return byte_placeholder;
}


unsigned int pwm_data_B()
{
	unsigned int temp;
	unsigned int byte_placeholder;
	unsigned int byte_placeholder1;
	unsigned int bit_to_check;
	unsigned int bit_to_shift,p1=0,p2=0,p3=0,p4=0;
	unsigned int predata,cnt1=0,data[20],i;
	int flag 			= 0;
	bit_to_check 		= 0x01;
	byte_placeholder	= 0x00;
	byte_placeholder1	= 0xFF80;
	predata				= 0x00;

	for(i=0;i<16;i++)
	{
		cnt1 = 0, cnt=0;
		while(cnt1==0)
		{
			cnt1 = cnt;
		}
		temp = PINB;
		if(CHECKBIT(temp, bit_to_check)){
			data[i] = 1;			
			}	
		else
			{
				data[i] =0;	
			}
		
		//flag++;
	}

	p1 = get_position(data[0],data[1],data[2],data[3]);
	p2 = get_position(data[4],data[5],data[6],data[7]);
	p3 = get_position(data[8],data[9],data[10],data[11]);
	p4 = get_position(data[12],data[13],data[14],data[15]);
	
	if(p1 == 0)
	{
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if (p1 == 1)
	{
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if(p1 == 2)
	{
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if(p1 ==3)
	{
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	if(p2 == 0)
	{
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if (p2 == 1)
	{
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if(p2 == 2)
	{
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if(p2==3)
	{
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	if(p3 == 0)
	{
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if (p3 == 1)
	{
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if(p3 == 2)
	{
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if(p3==3)
	{
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	if(p4 == 0)
	{
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if (p4 == 1)
	{
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if(p4 == 2)
	{
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x00;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	else if(p4 == 3)
	{
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
		bit_to_shift = 0x01;				
		byte_placeholder = byte_placeholder<<1;
		byte_placeholder = byte_placeholder|bit_to_shift;
	}
	return byte_placeholder;
}







//Main Program----------------------------------------------------------------------------
int main(void){

	serial_init(); 
	Timer1_init(); 
	DDRA=0x00;
	DDRB = 0x00;
	PORTB = 0xFF;
	PORTA=0xFF;
	TIMSK |= 0x04;
	SREG |= 0x80;
	unsigned int c,d,j, data[10];
	while(1){

	pwm_sync();

	data[0]=pwm_data_3();
	data[1]=pwm_data_3();
	data[2]=pwm_data_3();
	data[3]=pwm_data_3();
/*	pwm_sync_B();
	data[4] = pwm_data_B();
	data[5] = pwm_data_B();
	data[6] = pwm_data_B();
	data[7] = pwm_data_B();*/
	transmit(0xFF);
	transmit(0x80);
	transmit(data[0]);
	transmit(data[1]);
	transmit(data[2]);
	transmit(data[3]);
/*	transmit(data[4]);
	transmit(data[5]);
	transmit(data[6]);
	transmit(data[7]);*/
	transmit(0x00);

	/*syncHeaderPortA();
	for(j=0;j<4;j++)
	{
		data[j] = shiftByte();
	}
	syncHeaderPortB();
	for(j=4;j<8;j++)
	{
		data[j] = shiftByteB();
	}
	transmit(0xFF);
	transmit(0x80);
	for(j=0;j<8;j++)
	{
		transmit(data[j]);
	}

	transmit(0x00);
/*	for(j=0;j<4;j++)
		{
			c = shiftByte();
			transmit(c);
		}
//	transmit(0xFF);*/
/*	syncHeaderPortB();
	for(j=0;j<4;j++)
		{
			c = shiftByteB();
			transmit(c);
		}*/
	}

}
