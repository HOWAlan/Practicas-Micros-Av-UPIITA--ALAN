/*
 * practica 1b_2.c
 *
 * Created: 06/03/2023 06:00:27 p.m.
 * Author : Dell
 */ 
#define OUT_PORT PORTA
#define OUT_PORT_2 PORTB
#define TIME_DELAY 200
#define	F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>


int main(void)
{
	DDRA = 0xff;
	DDRB = 0xff;
	uint16_t j = 0x01;
	OUT_PORT = 0x01;
	OUT_PORT_2 = 0x01;
    /* Replace with your application code */
    while (1) 
    {
		for(int i = 0; i<15; i++)
		{
			_delay_ms(TIME_DELAY);
			j = (j<<1);
			OUT_PORT_2 = (j&0b0000000011111111);
			OUT_PORT = ((j>>8)%0b0000000011111111);
		}
		
		for(int i = 0; i<15; i++)
		{
			_delay_ms(TIME_DELAY);
			j = (j>>1);
			OUT_PORT_2 = (j&0b0000000011111111);
			OUT_PORT = ((j>>8)%0b0000000011111111);
		}
    }
}

