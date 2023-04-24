/*
 * practica5_timer_contador.c
 *
 * Created: 22/04/2023 12:47:23 p.m.
 *  Author: Alan
 */ 
#define F_CPU 1000000UL
#define PRELOAD 255
#define COUNT_LOC 10
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "LIB_UPIITA/UPIITA_LCD_LIB.h"

////////////////////////////////////////////////////////////////////////////////
//---------------------------funciones prototipo--------------------------------
void ConfigIO();

uint8_t itemCount = 0;
char countText[4]="\0";

ISR(TIMER0_OVF_vect){
	LIMPIA_LCD();
	ENVIA_CADENA("Objetos:");
	itemCount = 0;
}

int main(void)
{
	ConfigIO();
	LCD_INICIALIZA();
	ENVIA_CADENA("Objetos:");
	APAGAR_CURSOR();
	
    while(1)
    {
        itemCount = TCNT0;
		POS_LINEA1(COUNT_LOC);
		sprintf(countText,"%d",itemCount);
		ENVIA_CADENA(countText);
    }
}

void ConfigIO()
{
	cli();
	
	DDRC = 0XFF; //PUERTO DE LA LCD
	PORTC = 0X00;
	
	DDRB = 0b11111110;
	PORTB =0x01;//
	
	TCCR0 |=(1<<CS12)|(1<<CS11)|(1<<CS10);
	TIMSK |= (1<<TOIE0);
	
	//TCNT0 = PRELOAD;

	sei();
}
