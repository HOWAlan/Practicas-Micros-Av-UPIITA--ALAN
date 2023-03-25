/*
 * practica3_teclado_calc.c
 *
 * Created: 24/03/2023 09:12:15 p.m.
 *  Author: Alan
 */ 
#define F_CPU 1000000
#define WAIT_PROCESS 5
#define WAIT_PRESS_KEY 300
//--------------------------------------
//------------para la LCD---------------
#define LCD_PUERTO PORTC
#define LCD_RS PC2
#define  LCD_E PC3

#define IDLE_STATE			0
#define GET_NUM1_STATE		1
#define GET_MATH_OP_STATE	2
#define GET_NUM2_STATE		3
#define SHOW_RESULT_STATE	4
#define CALC_RESULT_STATE	5
#define RESET_STATE			6

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <util/delay.h>
#include <math.h>
#include "UPIITA_LIB/UPIITA_LCD_LIB.h"
#include "UPIITA_LIB/UPIITA_TECLADO_BARRIDO.h"

bool IsNumber(char x);
bool IsMathOp(char x);
char GetMathOp(char x);
uint16_t StringToUint16(char* array, uint8_t length);

int main(void)
{
	DDRC = 0XFF;
	DDRD = 0B11110000;
	DDRA = 0XFF;
	
	uint8_t state = RESET_STATE;
	char pressedKey = ' ';
	char mathOp = ' ';
	
	char calcScreen[17] = "\0";
	char texto[16]="\0";
	char num1[4] = "0000"; //CHAR ARRAY PARA NÚMERO 1
	char num2[4] = "0000"; //CHAR ARRAY PARA NÚMERO 2
	
	uint8_t num1Index = 0;
	uint8_t num2Index = 0;
	uint8_t calcScreenIndex = 0;
	
	uint16_t val1 = 0;
	uint16_t val2 = 0;
	uint32_t result = 0;
	LCD_INICIALIZA();
	//APAGAR_CURSOR();
	/* Replace with your application code */
	while (1)
	{
		switch(state)
		{
			case IDLE_STATE:
			//LCD MUESTRA TEXTO POR DEFAULT
			state = GET_NUM1_STATE;
			break;
			
			case GET_NUM1_STATE:
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
				else if(IsMathOp(pressedKey)) //comprobar operacion matematica presionada
				{
					//PORTA = 0B10101010;
					mathOp = GetMathOp(pressedKey);
					char texto[2] = {mathOp,'\0'};
					ENVIA_CADENA(texto);
					_delay_ms(WAIT_PRESS_KEY);
					val1 = StringToUint16(num1,num1Index);
					state = GET_NUM2_STATE;
				}
				else if(pressedKey == '#') //borrar
				{
					CURSOR_IZQ_CORRE();
					_delay_ms(WAIT_PROCESS);
					ENVIA_CADENA(" ");
					_delay_ms(WAIT_PROCESS);
					CURSOR_IZQ_CORRE();
					num1[num1Index] = '0';
					if (num1Index >0)
						num1Index--;
					_delay_ms(WAIT_PRESS_KEY);
				}
			break;
			
			case GET_MATH_OP_STATE:
			break;
			
			case GET_NUM2_STATE:
			BARRE_TECLADO();
			pressedKey = LEE_TECLADO();
			
			if((IsNumber(pressedKey))&(num2Index < 3))//Comprobar num presionado
			{
				//LIMPIA_LCD();
				//REGRESO_CASA();
				num2[num2Index] = pressedKey;
				//num1[num1Index+1] = '\0';
				ENVIA_DATO(pressedKey);
				num2Index++;
				_delay_ms(WAIT_PRESS_KEY);
			}
			else if(pressedKey =='*') //igual
			{
				//PORTA = 0B10101010;
				ENVIA_DATO('=');
				_delay_ms(WAIT_PRESS_KEY);
				val2 = StringToUint16(num2,num2Index);
				state = CALC_RESULT_STATE;
			}
			else if(pressedKey == '#') //borrar
			{
				CURSOR_IZQ_CORRE();
				_delay_ms(WAIT_PROCESS);
				ENVIA_CADENA(" ");
				_delay_ms(WAIT_PROCESS);
				CURSOR_IZQ_CORRE();
				num2[num2Index] = '0';
				if (num2Index >0)
					num2Index--;
				_delay_ms(WAIT_PRESS_KEY);
			}
			break;
			
			case CALC_RESULT_STATE:
				state = SHOW_RESULT_STATE;
				switch(mathOp)
				{
					case '+':
					result = val1+val2;
					PORTA = result;
					break;
					case '-':
					result = val1-val2;
					break;
					case 'X':
					result = val1*val2;
					break;
					case '/':
					result = val1/val2;
					break;
					default:
					break;
				}
			
			break;
			
			case SHOW_RESULT_STATE:
			POS_LINEA2(0);
			
			sprintf(texto,"%lu",result);
			ENVIA_CADENA(texto);
			state = IDLE_STATE;
			_delay_ms(WAIT_PRESS_KEY);
			break;
			
			case RESET_STATE:
			//LCD_HELLOWORLD();
			//_delay_ms(100);
			LIMPIA_LCD();
			_delay_ms(WAIT_PROCESS);
			REGRESO_CASA();
			_delay_ms(WAIT_PROCESS);
			state = IDLE_STATE;
			break;
			
			default:
			break;
		}
		
	}
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

bool IsMathOp(char x)
{
	/*	A    +
	*	B    -
	*	C    X
	*	D    /
	*/
	bool result = false;
	if((x>=65)&(x<=68))
	{
		result = true;
	}
	return result;
}

char GetMathOp(char x)
{
	char result = ' ';
	switch(x)
	{
		case 'A':
		result = '+';
		break;
		
		case 'B':
		result = '-';
		break;
		
		case 'C':
		result = 'X';
		break;
		
		case 'D':
		result = '/';
		break;
	}
	return result;
 }
 uint16_t StringToUint16(char* array, uint8_t length)
 {
	 uint16_t result = 0;
	 switch(length)
	 {
		case 1:
		result = ((array[0]-48)*1);
		break;
		
		case 2:
		result = ((array[0]-48)*10)+((array[1]-48)*1);
		break;
		
		case 3:
		result = ((array[0]-48)*100)+((array[1]-48)*10)+((array[2]-48)*1);
		break; 
	 }
	 return result;
 }
