
#define F_CPU 1000000
#define WAIT_PROCESS 5
#define WAIT_PRESS_KEY 400
#define MESSAGE_1	"Angulo ="
#define MESSAGE_2	"NUEVO ="

#define CURRENT_DC_LOC 9
#define NEW_DC_LOC 8

#define OCR1X_AT_0D 62.46
#define TIME_X_DEGREE 1.111E-5
#define TIME_X_UNIT 8.0039E-6

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
void SetOCRValue(uint8_t degree);

ISR(TIMER1_COMPA_vect)
{
	PORTD=PIND;
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
			SetOCRValue(val1);
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
	DDRB = 0B11110000;//teclado
	DDRD = 0xff;  //motor

	TCCR1A |= (1<<WGM11)|(0<<WGM10)|(1<<COM1A1)|(0<<COM1A0); // CTC
	TCCR1B|= (0<<CS12)|(1<<CS11)|(0<<CS10)|(1<<WGM13)|(1<<WGM12);//no prescaling N=1
	ICR1 = 0b0000011111111111;
	OCR1A = 312; // PRELOAD DUTY CYCLE
	
	TIMSK |= (1<<OCIE1A);//OUTPUT COMPARE INTERRUPT ENABLE
	
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
	
	if(resultAux>180)
	{
		result = 180;
	}
	else
	{
		result = (uint8_t)resultAux;
	}
	
	return result;
}

void SetOCRValue(uint8_t degree)
{	
	if (degree>180)
	degree = 180;
	
	if (degree==0)
	{
		OCR1A = (uint16_t)OCR1X_AT_0D;
		//printf("valor OCR1A %d",OCR1A);
	}
	else
	{
		float auxVar = (((float)degree*TIME_X_DEGREE)/TIME_X_UNIT)+OCR1X_AT_0D;
		OCR1A = (uint16_t)auxVar;
		//printf("\n valor calculado %f", auxVar);
		//printf("\n valor OCR1A %d", OCR1A);
	}
}