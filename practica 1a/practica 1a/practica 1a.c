/*
 * practica_1a.c
 *
 * Created: 27/02/2023 10:32:46 p.m.
 *  Author: Alan
 */ 
#define WAIT_TIME 500
#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>

int i = 0b00001111;
int j = 0b11110000;
int c = 0;

int main(void)
{
	//config
	DDRA = 0XFF;
	DDRB = 255;
	DDRC = 0B11111111;
	DDRD = 0XFF;
	
    while(1)
    {
		PORTA = i;
		PORTB = j;
		PORTC = i;
		PORTD = j;
		
		_delay_ms(WAIT_TIME);
		
		PORTA = j;
		PORTB = i;
		PORTC = j;
		PORTD = i;
		
		_delay_ms(WAIT_TIME);
		
		PORTA = c;
		PORTB = c;
		PORTC = c;
		PORTD = c;
		
		_delay_ms(WAIT_TIME);
        //TODO:: Please write your application code 
    }
}