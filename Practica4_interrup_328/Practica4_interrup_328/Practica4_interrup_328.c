/*
 * Practica4_interrup_328.c
 *
 * Created: 29/03/2023 10:23:52 p.m.
 *  Author: Alan
 */ 


#define F_CPU 1000000UL
#define WAIT_LED 200
#define LEDS_PORT PORTD
#define LEDS_DDR DDRD

#define SEQUENCE1 0
#define SEQUENCE2 1
#define SEQUENCE3 2

#define INT0_  0b00000110
#define INT1_  0b00000101
#define INT2_  0b00000011

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

////////////////////////////////////////////////////////////////////////////////
//---------------------------funciones prototipo--------------------------------
void LedSequence1();
void LedSequence2();
void LedSequence3();

////////////////////////////////////////////////////////////////////////////////
//------------------------Declaración de variables globales---------------------

uint8_t output = 0x01;
uint8_t	sequencePointer = SEQUENCE2;

////////////////////////////////////////////////////////////////////////////////
//---------------------------Vectores de interrupción-------------------------
ISR(PCINT0_vect){
	//PORTC = PINB&0b00000111;
	switch(PINB&0b00000111)
	{
		case INT0_:
		PORTC = PINB;
		sequencePointer = SEQUENCE1;
		break;
		
		case INT1_:
		PORTC = PINB;
		sequencePointer = SEQUENCE2;
		break;
		
		case INT2_:
		PORTC = PINB;
		sequencePointer = SEQUENCE3;
		break;
		
		default:
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////


void ConfigIO()
{
	cli();
	LEDS_DDR = 0xFF;//SALIDAS PARA LEDS
	LEDS_PORT = 0X00;// VALOR INICIAL
	
	DDRC = 0xff;
	PORTC =0x00;
	DDRB = 0B11111000; //INTERRUPCIONES
	PORTB = 0B00000111;//PULLUP ENABLE

	//-----------CONFIGURAR INTERRUPCIONES---------
	PCICR|=(1<<PCIE0); //ACTIVA PCINT0
	PCMSK0 |= (1<<PCINT0)|(1<<PCINT1)|(1<<PCINT2);
	sei();
}


int main(void)
{
	ConfigIO(); //CONFIGURAR ENTRADAS Y SALIDAS
	
	/* Replace with your application code */
	while (1)
	{
		switch(sequencePointer)
		{
			case SEQUENCE1:
			LedSequence1();
			break;
			
			case SEQUENCE2:
			LedSequence2();
			break;
			
			case SEQUENCE3:
			LedSequence3();
			break;
			
			default:
			//LedSequence2();
			break;
		}
	}
}


////////////////////////////////////////////////////////////////////////////////
//--------------------------program's functions------------------------------

void LedSequence1()
{
	output = 0x01;
	LEDS_PORT = output;
	for(uint8_t j=0; j<7; j++)
	{
		if(sequencePointer!= SEQUENCE1) // go out if interrupt has occurred
		return;
		
		_delay_ms(WAIT_LED);
		output = (output<<1);
		LEDS_PORT = output;
	}
	
	for(uint8_t j=0; j<7; j++)
	{
		if(sequencePointer!= SEQUENCE1) // go out if interrupt has occurred
			return;
		
		_delay_ms(WAIT_LED);
		output = (output>>1);
		LEDS_PORT = output;
	}
	return;
}
//--------------------------------------------------------------------------------

void LedSequence2()
{
	uint8_t varAux = 0x00;
	output = 0X00;
	LEDS_PORT = output;
	_delay_ms(300);
	for(uint8_t j = 8; j>0; j--)
	{
		varAux = 0x01;
		for(uint8_t k = 0; k<j; k++)
		{
			if(sequencePointer!= SEQUENCE2) // go out if interrupt has occurred
				return;
			varAux=(1<<k);
			LEDS_PORT=output|varAux;
			_delay_ms(200);
		}
		output |= varAux;
		LEDS_PORT = output;
	}
	_delay_ms(WAIT_LED);
}

void LedSequence3()
{
	for(uint8_t i = 0; i<3; i++)
	{
			output = 0xff;
			LEDS_PORT = output;
			_delay_ms(150);
			output = 0x00;
			LEDS_PORT = output;
			_delay_ms(90);
	}
	_delay_ms(300);
}