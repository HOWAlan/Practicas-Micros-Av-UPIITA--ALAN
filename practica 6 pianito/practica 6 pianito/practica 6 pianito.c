/*
 * practica_6_pianito.c
 *
 * Created: 02/05/2023 08:23:00 p.m.
 *  Author: Alan
 */ 

#define F_CPU 1000000UL
#define BUFFER DDRB
#define START_MESSAGE_POS 7

#define	_DO 58
#define _DO_S 55
#define _RE 52
#define _RE_S 49
#define _MI 46
#define _FA 43
#define _FA_S 40
#define _SOL 38
#define _SOL_S 36
#define _LA 34
#define _LA_S 32
#define _SI 30

#define SOUND_ENABLE 255
#define SOUND_DISABLE 247

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "LIB_UPIITA/UPIITA_LCD_LIB.h"
#include "LIB_UPIITA/UPIITA_TECLADO_BARRIDO.h"

////////////////////////////////////////////////////////////////////////////////
//---------------------------funciones prototipo--------------------------------
void ConfigIO();

char pressedKey = ' ';

ISR(TIMER0_COMP_vect)
{
	PORTB = PINB;
}
int main(void)
{
	ConfigIO();
	DisableSound();
	LCD_INICIALIZA(); //INICIALIZAR LCD
	APAGAR_CURSOR();
	
    while(1)
    {
		for (uint8_t i =0;i<4;i++)
		{
			BARRE_TECLADO();
			pressedKey = LEE_TECLADO();
			if(pressedKey!=' ')
			{
				EnableSound();
				break;
			}
		}
		
		switch(pressedKey)
		{
			case '1':
				ChangeNote(_DO);
				RefreshLCDMessage("Do");
				EnableSound();
			break;
			
			case '2':
				ChangeNote(_DO_S);
				RefreshLCDMessage("Do#");
			break;
			
			case '3':
				ChangeNote(_RE);
				RefreshLCDMessage("Re");
			break;
			
			case 'A':
				ChangeNote(_RE_S);
				RefreshLCDMessage("Re#");
			break;
			
			case '4':
				ChangeNote(_MI);
				RefreshLCDMessage("Mi");
			break;
			
			case '5':
				ChangeNote(_FA);
				RefreshLCDMessage("Fa");
			break;
			
			case '6':
				ChangeNote(_FA_S);
				RefreshLCDMessage("FA#");
			break;
			
			case 'B':
				ChangeNote(_SOL);
				RefreshLCDMessage("Sol");
			break;
			
			case '7':
				ChangeNote(_SOL_S);
				RefreshLCDMessage("Sol#");
			break;
			
			case '8':
				ChangeNote(_LA);
				RefreshLCDMessage("La");
			break;
			
			case '9':
				ChangeNote(_LA_S);
				RefreshLCDMessage("La#");
			break;
			
			case 'C':
				ChangeNote(_SI);
				RefreshLCDMessage("Si");
			break;
			
			default:
				DisableSound();
			break;
		}
        //TODO:: Please write your application code 
    }
}

void ConfigIO()
{
	cli();
	DDRC = 0XFF;
	DDRD = 0B11110000;
	DDRB |= (1<<DDB3);
	TCCR0 = (1<<WGM01)|(0<<WGM00)|(0<<COM01)|(1<<COM00);
	TCCR0|= (1<<CS02)|(0<<CS01)|(0<<CS00); //PREESCALA 256
	OCR0 = _DO;
	TIMSK = (1<<OCIE0);
	sei();
}
void RefreshLCDMessage(char note[4])
{
	LIMPIA_LCD();
	POS_LINEA1(START_MESSAGE_POS);
	ENVIA_CADENA(note);
}
void ChangeNote(uint8_t value)
{
	OCR0 = value;
}
void DisableSound()
{
	cli();
	PORTB = 0x00;
	TCCR0&= ~(1<<COM00);//desactivar ctc mode
}
void EnableSound()
{
	TCCR0|=(1<<COM00);//activar ctc mode
	sei();
}