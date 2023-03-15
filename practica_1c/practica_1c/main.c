/*
 * practica_1c.c
 *
 * Created: 06/03/2023 06:22:26 p.m.
 * Author : Dell
 */ 
#define F_CPU 1000000
#define WAIT_TIME 250
#define	PULL_UP_EN 1
#include <avr/io.h>
#include <util/delay.h>

int i_o = 0;

int main(void)
{
	DDRA = 0X00;
	DDRB = 0XFF;
	PORTA = 0XFF;
    /* Replace with your application code */
    while (1) 
    {
		i_o = PINA;
		_delay_ms(WAIT_TIME);
		PORTB = i_o;
    }
}

