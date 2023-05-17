/*
 * practica_7.c
 *
 * Created: 08/05/2023 12:38:07 p. m.
 * Author : ing_0
 */ 

#define F_CPU 1000000
#define WAIT_PROCESS 5
#define WAIT_PRESS_KEY 400
#define MESSAGE_1	"D.C="
#define MESSAGE_2	"NUEVO D.C=" 

#define CURRENT_DC_LOC 5
#define NEW_DC_LOC 11

//--------------------------------------
//------------para la LCD---------------
#define LCD_PUERTO PORTC
#define LCD_RS PC2
#define  LCD_E PC3

#define IDLE_STATE			0
#define GET_DUTY_CYCLE		1
#define SET_DUTY_CYCLE		2
#define CHANGE_SCREEN		3
#define RESET_STATE			6
#define RESTART_STATE		7

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <util/delay.h>
#include <math.h>
#include "UPIITA_LIB/UPIITA_LCD_LIB.h"
#include "UPIITA_LIB/UPIITA_TECLADO_BARRIDO.h"

bool IsNumber(char x);
uint8_t StringToUint8(char* array, uint8_t length);

ISR(TIMER0_COMP_vect)
{
	PORTB=PINB;
}

int main(void)
{
	uint8_t state = IDLE_STATE;
	char pressedKey = ' ';
	char num1[4] = "0000"; //CHAR ARRAY PARA NÚMERO 1
	uint8_t val1 = 0;
	uint8_t num1Index = 0;
	char texto[5]="\0";
	ConfigIO();
	LCD_INICIALIZA(); //INICIALIZAR LCD
	POS_LINEA1(0);
	ENVIA_CADENA(MESSAGE_1);
	POS_LINEA2(0);
	ENVIA_CADENA(MESSAGE_2);
	APAGAR_CURSOR();
	
    /* Replace with your application code */
    while (1) 
    {
		switch(state)
		{
			case IDLE_STATE:
				POS_LINEA1(CURRENT_DC_LOC);
				POS_LINEA2(NEW_DC_LOC);
				state = GET_DUTY_CYCLE;
			break;
			
			case GET_DUTY_CYCLE:
				BARRE_TECLADO();
				pressedKey = LEE_TECLADO();
			
				if((IsNumber(pressedKey))&(num1Index < 3))//Comprobar num presionado
				{
					//LIMPIA_LCD();
					//REGRESO_CASA();
					num1[num1Index] = pressedKey;
					//num1[num1Index+1] = '\0';
					ENVIA_DATO(pressedKey);
					num1Index++;
					_delay_ms(WAIT_PRESS_KEY);
				}
				else if(pressedKey == '#') //borrar
				{
					if(num1Index>0)
					{
						CURSOR_IZQ_CORRE();
						_delay_ms(WAIT_PROCESS);
						ENVIA_CADENA(" ");
						_delay_ms(WAIT_PROCESS);
						CURSOR_IZQ_CORRE();
						num1[num1Index] = '0';
						num1Index--;
						_delay_ms(WAIT_PRESS_KEY);
					}
				}
				else if(pressedKey == 'A')//tecla aceptar
				{
					_delay_ms(WAIT_PRESS_KEY);
					val1 = StringToUint8(num1,num1Index);
					state = SET_DUTY_CYCLE;
					_delay_ms(WAIT_PRESS_KEY);
				}
				
			break;
			
			case SET_DUTY_CYCLE:
				OCR0 = val1;//set duty cycle
				state = CHANGE_SCREEN;				
			break;
			
			case CHANGE_SCREEN:
			
				POS_LINEA1(CURRENT_DC_LOC);//-------
				ENVIA_CADENA("    ");// lIMPIAR EL DC ANTERIOR EN PANTALLA
				
				POS_LINEA1(CURRENT_DC_LOC);//POSICIONAR CURSOR
				sprintf(texto,"%d",val1);
				ENVIA_CADENA(texto);//ACTUALIZAR VALOR DEL DC EN PANTALLA
				
				state = RESTART_STATE;
				_delay_ms(WAIT_PRESS_KEY);
			break;
			
			case RESET_STATE:
			break;
			
			case RESTART_STATE:
				POS_LINEA2(NEW_DC_LOC);//-------
				ENVIA_CADENA("    ");// lIMPIAR EL DC ANTERIOR EN PANTALLA
				
				POS_LINEA2(NEW_DC_LOC);//RECOLOCAR PUNTERO DE PANTALLA
				state = IDLE_STATE;
				_delay_ms(WAIT_PRESS_KEY);
				
				
				val1 = 0;
				num1Index = 0;
			break;
			
			default:
			break;
		}
    }
}

void ConfigIO()
{
	cli();
	DDRC = 0XFF; //lcd
	DDRD = 0B11110000;//teclado
	DDRB = 0xff;  //motor

	TCCR0 |= (0<<WGM01)|(1<<WGM00)|(1<<COM01)|(0<<COM00); // CTC
	TCCR0|= (0<<CS02)|(0<<CS01)|(1<<CS00);//no prescaling N=1
	OCR0 = 128; // PRELOAD DUTY CYCLE
	
	TIMSK |= (1<<OCIE0);//OUTPUT COMPARE INTERRUPT ENABLE
	 
	sei();
}

bool IsNumber(char x)
{
	bool result = false;
	if((x>=0x30)&(x<=0x39))
	{
		result = true;
	}
	return result;
}

uint8_t StringToUint8(char* array, uint8_t length)
{
	uint8_t result = 0;
	uint16_t resultAux = 0;
	
	switch(length)
	{
		case 1:
		resultAux = ((array[0]-48)*1);
		break;
		
		case 2:
		resultAux = ((array[0]-48)*10)+((array[1]-48)*1);
		break;
		
		case 3:
		resultAux = ((array[0]-48)*100)+((array[1]-48)*10)+((array[2]-48)*1);
		break;
	}
	
	if(resultAux>255)
	{
		result = 255;
	}
	else
	{
		result = (uint8_t)resultAux;
	}
	
	return result;
}