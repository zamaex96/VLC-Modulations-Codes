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
//	TCCR1B |= (1 << CS11) | (1 << CS10);	// prescale: clk / 64

	

}

ISR(TIMER1_OVF_vect)
{
	cnt++;
}
//---------------------------------------------------Header Synchronization----------------------------------------------

unsigned int sync_mppm()
{
	unsigned int temp,temp2,temp3,temp4;
	unsigned int byte_placeholder;
	unsigned int byte_placeholder1,i=0;
	unsigned int bit_to_check;
	unsigned int bit_to_shift;
	unsigned int predata,cnt1=0;
	bit_to_check 		= 0x01;
	byte_placeholder	= 0x00;
	byte_placeholder1	= 0xFF80;
	predata				= 0x00;

	temp = PINA;

	while(!(CHECKBIT(temp, bit_to_check))){temp = PINA; }//transmit(0x88);}

	while(1)
	{
		
		temp =PINA;
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
			i++;
			
			cnt1 = 0, cnt=0;
			while(cnt1==0)
			{
				cnt1 = cnt;
			}
			if(byte_placeholder == 0xAAAA)
			break;

	}


}

unsigned int sync_mppm_B()
{
	unsigned int temp,temp2,temp3,temp4;
	unsigned int byte_placeholder;
	unsigned int byte_placeholder1,i=0;
	unsigned int bit_to_check;
	unsigned int bit_to_shift;
	unsigned int predata,cnt1=0;
	bit_to_check 		= 0x01;
	byte_placeholder	= 0x00;
	byte_placeholder1	= 0xFF80;
	predata				= 0x00;

	temp = PINB;

	while(!(CHECKBIT(temp, bit_to_check))){temp = PINB; }//transmit(0x88);}

	while(1)
	{
		
		temp =PINB;
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
			i++;
			
			cnt1 = 0, cnt=0;
			while(cnt1==0)
			{
				cnt1 = cnt;
			}
			if(byte_placeholder == 0xAAAA)
			break;

	}


}

// --------------------------- Data Detection ----------------------------------





unsigned int data_mppm(){

	unsigned int temp;
	unsigned int byte_placeholder;
	unsigned int byte_placeholder1;
	unsigned int bit_to_check;
	unsigned int bit_to_shift,raw[20],i=0;
	unsigned int predata,cnt1=0;
	int flag 			= 0;
	bit_to_check 		= 0x01;
	byte_placeholder	= 0x00;
	byte_placeholder1	= 0xFF80;
	predata				= 0x00;

	while(flag<16)
	{
		temp = PINA;
		if(CHECKBIT(temp, bit_to_check)){
			
			raw[i] = 1;
		}
		else
		{
			raw[i] = 0;
		}
		flag++;
		i++;
		cnt1 = 0, cnt=0;
		while(cnt1==0)
		{
			cnt1 = cnt;
		}
		
	
	}

	for(i=0;i<16;i+=4)
	{
	if(raw[i] == 0)
	{
		if(raw[i+1]==0)
		{
			if(raw[i+2] == 1)
			{
				bit_to_shift = 0x01;				
				byte_placeholder = byte_placeholder<<1;
				byte_placeholder = byte_placeholder|bit_to_shift;
				bit_to_shift = 0x00;				
				byte_placeholder = byte_placeholder<<1;
				byte_placeholder = byte_placeholder|bit_to_shift;
			}
		}
		else
		{
			if(raw[i+2] == 1)
			{
				bit_to_shift = 0x00;				
				byte_placeholder = byte_placeholder<<1;
				byte_placeholder = byte_placeholder|bit_to_shift;
				bit_to_shift = 0x01;				
				byte_placeholder = byte_placeholder<<1;
				byte_placeholder = byte_placeholder|bit_to_shift;
			}
		}
	}
	else
	{
		if(raw[i+1] == 1)
		{
			if(raw[i+2] == 0)
			{
				bit_to_shift = 0x00;				
				byte_placeholder = byte_placeholder<<1;
				byte_placeholder = byte_placeholder|bit_to_shift;
				bit_to_shift = 0x00;				
				byte_placeholder = byte_placeholder<<1;
				byte_placeholder = byte_placeholder|bit_to_shift;
			}
		}
		else
		{
			if(raw[i+2] == 1)
			{
				bit_to_shift = 0x01;				
				byte_placeholder = byte_placeholder<<1;
				byte_placeholder = byte_placeholder|bit_to_shift;
				bit_to_shift = 0x01;				
				byte_placeholder = byte_placeholder<<1;
				byte_placeholder = byte_placeholder|bit_to_shift;
			}
		}
	}
	}
	
	return byte_placeholder;

}


unsigned int data_mppm_B(){

	unsigned int temp;
	unsigned int byte_placeholder;
	unsigned int byte_placeholder1;
	unsigned int bit_to_check;
	unsigned int bit_to_shift,raw[20],i=0;
	unsigned int predata,cnt1=0;
	int flag 			= 0;
	bit_to_check 		= 0x01;
	byte_placeholder	= 0x00;
	byte_placeholder1	= 0xFF80;
	predata				= 0x00;

	while(flag<16)
	{
		temp = PINB;
		if(CHECKBIT(temp, bit_to_check)){
			
			raw[i] = 1;
		}
		else
		{
			raw[i] = 0;
		}
		flag++;
		i++;
		cnt1 = 0, cnt=0;
		while(cnt1==0)
		{
			cnt1 = cnt;
		}
		
	
	}

	for(i=0;i<16;i+=4)
	{
	if(raw[i] == 0)
	{
		if(raw[i+1]==0)
		{
			if(raw[i+2] == 1)
			{
				bit_to_shift = 0x01;				
				byte_placeholder = byte_placeholder<<1;
				byte_placeholder = byte_placeholder|bit_to_shift;
				bit_to_shift = 0x00;				
				byte_placeholder = byte_placeholder<<1;
				byte_placeholder = byte_placeholder|bit_to_shift;
			}
		}
		else
		{
			if(raw[i+2] == 1)
			{
				bit_to_shift = 0x00;				
				byte_placeholder = byte_placeholder<<1;
				byte_placeholder = byte_placeholder|bit_to_shift;
				bit_to_shift = 0x01;				
				byte_placeholder = byte_placeholder<<1;
				byte_placeholder = byte_placeholder|bit_to_shift;
			}
		}
	}
	else
	{
		if(raw[i+1] == 1)
		{
			if(raw[i+2] == 0)
			{
				bit_to_shift = 0x00;				
				byte_placeholder = byte_placeholder<<1;
				byte_placeholder = byte_placeholder|bit_to_shift;
				bit_to_shift = 0x00;				
				byte_placeholder = byte_placeholder<<1;
				byte_placeholder = byte_placeholder|bit_to_shift;
			}
		}
		else
		{
			if(raw[i+2] == 1)
			{
				bit_to_shift = 0x01;				
				byte_placeholder = byte_placeholder<<1;
				byte_placeholder = byte_placeholder|bit_to_shift;
				bit_to_shift = 0x01;				
				byte_placeholder = byte_placeholder<<1;
				byte_placeholder = byte_placeholder|bit_to_shift;
			}
		}
	}
	}
	
	return byte_placeholder;

}

//Main Program----------------------------------------------------------------------------
int main(void){

	serial_init(); 
	Timer1_init(); 
	DDRA=0x00;
	DDRB = 0x00;
	PORTA=0xFF;
	PORTB=0xFF;
	TIMSK |= 0x04;
	SREG |= 0x80;
	unsigned int data[20];
	unsigned int c,j;
	while(1){
	sync_mppm();
	data[0] = data_mppm();
	data[1] = data_mppm();
	data[2] = data_mppm();
	data[3] = data_mppm();
	data[4] = data_mppm();
	data[5] = data_mppm();
	data[6] = data_mppm();
	data[7] = data_mppm();
	data[8] = data_mppm();
	/*sync_mppm_B();
	data[9] = data_mppm_B();
	data[10] = data_mppm_B();
	data[11] = data_mppm_B();
	data[12] = data_mppm_B();
	data[13] = data_mppm_B();
	data[14] = data_mppm_B();
	data[15] = data_mppm_B();
	data[16] = data_mppm_B();
	data[17] = data_mppm_B();*/
	transmit(0xFF);
	transmit(0x80);
	for(j=0;j<9;j++)
	{
		transmit(data[j]);
	}
	transmit(0x00);
	}

}
