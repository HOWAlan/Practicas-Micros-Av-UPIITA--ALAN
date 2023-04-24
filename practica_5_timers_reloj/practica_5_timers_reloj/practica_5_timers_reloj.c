/*
 * practica_5_timers_reloj.c
 *
 * Created: 21/04/2023 11:19:53 p.m.
 *  Author: Alan
 */ 

#define F_CPU 1000000UL
#define SECONDS_LOC 11
#define MINUTES_LOC 8
#define HOURS_LOC 5
#define PRELOAD 49911

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "LIB_UPIITA/UPIITA_LCD_LIB.h"

////////////////////////////////////////////////////////////////////////////////
//---------------------------funciones prototipo--------------------------------
void ConfigIO();
void UpdateTime();

char texto[3]="\0";

short int i=0;
static uint8_t seconds = 55;
static uint8_t minutes = 9;
static uint8_t hours = 9;

ISR (TIMER1_OVF_vect) {
	if(seconds<59){
		seconds++;
	}else{
		seconds =0;
		if(minutes<59){
			minutes++;
		}else{
			minutes=0;
			if(hours<24){
				hours++;
			}else{
				hours=0;
			}
		}
	}
	TCNT1 = PRELOAD;
	PORTB ^=0X01;
	UpdateTime();
}

int main(void)
{
	ConfigIO(); //CONFIGURAR ENTRADAS Y SALIDAS
	LCD_INICIALIZA(); //INICIALIZAR LCD
	POS_LINEA1(HOURS_LOC);
	ENVIA_CADENA("00:00:00");
	APAGAR_CURSOR();
	
	while(1)
	{
		//bucle infinito
	}
}


void ConfigIO()
{
	cli();
	
	DDRC = 0XFF; //PUERTO DE LA LCD
	PORTC = 0X00;
	
	DDRB = 0xff;
	PORTB =0x00;//LED TESTIGO
	
	TCCR1B |=(0<<CS12)|(1<<CS11)|(1<<CS10);
	TIMSK |= (1<<TOIE1);
	
	TCNT1 = PRELOAD;

	sei();
}

void UpdateTime(){
	
	sprintf(texto,"%d",seconds);
	if(seconds<10){
		POS_LINEA1(SECONDS_LOC);
		ENVIA_CADENA("0");
		POS_LINEA1(SECONDS_LOC+1);
	}
	else{
		POS_LINEA1(SECONDS_LOC);
	}
	ENVIA_CADENA(texto);
	
	sprintf(texto,"%d",minutes);
	if(minutes<10){
		POS_LINEA1(MINUTES_LOC);
		ENVIA_CADENA("0");
		POS_LINEA1(MINUTES_LOC+1);
	}
	else{
		POS_LINEA1(MINUTES_LOC);
	}
	ENVIA_CADENA(texto);
	
	sprintf(texto,"%d",hours);
	if(hours<10){
		POS_LINEA1(HOURS_LOC);
		ENVIA_CADENA("0");
		POS_LINEA1(HOURS_LOC+1);
	}
	else{
		POS_LINEA1(HOURS_LOC);
	}
	ENVIA_CADENA(texto);
	
}