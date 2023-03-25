/*
 * Practica3_a_teclado.c
 *
 * Created: 23/03/2023 07:04:32 p.m.
 *  Author: Alan
 */ 

#define F_CPU 1000000
#define WAIT_PROCESS 5
#define WAIT_PRESS_KEY 500
//--------------------------------------
//------------para la LCD---------------
#define LCD_PUERTO PORTC
#define LCD_RS PC2
#define  LCD_E PC3

#include <avr/io.h>
#include <util/delay.h>
#include "UPIITA_LIB/UPIITA_LCD_LIB.h"
#include "UPIITA_LIB/UPIITA_TECLADO_BARRIDO.h"

int main(void)
{
	char pressedKey = ' ';
	DDRC = 0XFF;
	DDRD = 0B11110000;
	DDRA = 0XFF;
	LCD_PUERTO = 0X00;
	LCD_INICIALIZA();
	_delay_ms(WAIT_PROCESS);
	CARGAR_CAR_ESP();
	//LCD_HELLOWORLD();
	
    while(1)
    {
		BARRE_TECLADO();
		_delay_ms(WAIT_PROCESS);
		pressedKey = LEE_TECLADO();
		
		char cadena[2] = {pressedKey,'\0'};
		 
		if (pressedKey!=' ')
		{
			switch(pressedKey)
			{
				case 'A':
					ENVIA_DATO(4);
					_delay_ms(WAIT_PRESS_KEY);
				break;
				case 'B':
					ENVIA_DATO(5);
					_delay_ms(WAIT_PRESS_KEY);
				break;
				case 'C':
					ENVIA_DATO(6);
					_delay_ms(WAIT_PRESS_KEY);
				break;
				case 'D':
					ENVIA_DATO(7);
					_delay_ms(WAIT_PRESS_KEY);
				break;
				case '#': //SALTO DE LINEA
					POS_LINEA2(0);
					_delay_ms(WAIT_PRESS_KEY);
				break;
				case '*'://BORRAR
					CURSOR_IZQ_CORRE();
					_delay_ms(WAIT_PROCESS);
					ENVIA_CADENA(" ");
					_delay_ms(WAIT_PROCESS);
					CURSOR_IZQ_CORRE();
					_delay_ms(WAIT_PRESS_KEY);
				break;
				default:
					ENVIA_CADENA(cadena);
					_delay_ms(WAIT_PRESS_KEY);
				break;
			}
		}
		
        //TODO:: Please write your application code 
    }
}