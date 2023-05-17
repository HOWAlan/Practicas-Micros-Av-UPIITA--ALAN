/*
 * practica_6_cancion.c
 *
 * Created: 04/05/2023 11:08:08 p.m.
 *  Author: Alan
 */ 
#define F_CPU 1000000UL

#define	_DO 237
#define _DO_S 224
#define _RE 211
#define _RE_S 199
#define _MI 188
#define _FA 177
#define _FA_S 167
#define _SOL 158
#define _SOL_S 149
#define _LA 141
#define _LA_S 133
#define _SI 125
#define _DO_5 118
#define _RE_5 105
#define _RE_S_5 99
#define _FA_5 88
#define _SOL_5 78
#define _LA_5 70
#define _LA_S_5 66
#define SILENCE			0

#define N				8
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>

void ConfigIO();
void Play(uint8_t note, uint16_t duration);

volatile uint16_t pulsesCounter = 0;

ISR(TIMER0_COMP_vect)
{
	PORTB = PINB;
	pulsesCounter++;
}

int main(void)
{
	ConfigIO();
    while(1)
    {
		
        Play(_RE_5,250);
		Play(SILENCE,10);
		Play(_RE_5,250);
		Play(SILENCE,10);
		Play(_RE_5,250);
		Play(SILENCE,10);
		Play(_RE_5,500);
		
		Play(SILENCE,250);
		
		Play(_RE_5,250);
		Play(SILENCE,10);
		Play(_DO_5,500);
		Play(SILENCE,10);
		Play(_LA_S,250);
		Play(SILENCE,10);
		Play(_FA,500);
		
		Play(SILENCE,500);
		
		Play(_LA_S,250);
		Play(SILENCE,10);
		Play(_RE_5,500);
		Play(SILENCE,10);
		Play(_RE_5,500);
		Play(SILENCE,10);
		Play(_DO_5,250);
		Play(SILENCE,10);
		Play(_LA_S,250);
		Play(SILENCE,10);
		Play(_DO_5,1000);
		Play(SILENCE,2000);
		
		Play(_LA_S,250);
		Play(SILENCE,10);
		Play(_RE_S_5,250);
		Play(SILENCE,10);
		Play(_RE_S_5,250);
		Play(SILENCE,10);
		Play(_RE_S_5,500);
		Play(SILENCE,10);
		Play(_FA_5,250);
		Play(SILENCE,10);
		Play(_RE_5,500);
		Play(SILENCE,10);
		Play(_DO_5,500);
		Play(SILENCE,10);
		Play(_LA_S,500);
		Play(SILENCE,500);
		Play(_LA_S,250);
		Play(SILENCE,10);
		Play(_RE_5,500);
		Play(SILENCE,10);
		Play(_RE_5,250);
		Play(SILENCE,10);
		Play(_DO_5,500);
		Play(SILENCE,10);
		Play(_LA_S,250);
		Play(SILENCE,10);
		Play(_RE_5,1250);
		Play(SILENCE,1000);
		//POKEMON--------
		/*
		Play(_RE,250);
		Play(SILENCE,10);
		Play(_FA,250);
		Play(SILENCE,10);
		Play(_SOL,1000);
		Play(SILENCE,10);
		Play(_RE,250);
		Play(SILENCE,10);
		Play(_RE,250);
		Play(SILENCE,10);
		Play(_FA,250);
		Play(SILENCE,10);
		Play(_SOL,500);
		Play(SILENCE,10);
		Play(_SOL,250);
		Play(SILENCE,10);
		Play(_FA,250);
		Play(SILENCE,10);
		Play(_RE,250);
		Play(SILENCE,10);
		Play(_DO,250);
		Play(SILENCE,10);
		Play(_DO,250);
		Play(SILENCE,10);
		Play(_LA_S,1000);
		Play(SILENCE,10);
		
		Play(_SOL,250);
		Play(SILENCE,10);
		Play(_LA_S,250);
		Play(SILENCE,10);
		Play(_DO_5,250);
		Play(SILENCE,10);
		Play(_RE_5,250);
		Play(SILENCE,10);
		Play(_DO_5,500);
		Play(SILENCE,10);
		Play(_LA_S,500);
		Play(SILENCE,10);
		Play(_FA_5,1000);
		Play(SILENCE,10);
		*/
		
		
		Play(_RE,250);
		Play(SILENCE,10);
		Play(_FA,250);
		Play(SILENCE,10);
		Play(_SOL,750);
		Play(SILENCE,10);
		Play(_RE,250);
		Play(SILENCE,10);
		Play(_RE,250);
		Play(SILENCE,10);
		Play(_FA,250);
		Play(SILENCE,10);
		Play(_SOL,250);
		Play(SILENCE,10);
		Play(_FA,250);
		Play(SILENCE,10);
		Play(_SOL,250);
		Play(SILENCE,10);
		Play(_FA_5,500);
		Play(SILENCE,10);
		Play(_RE_5,250);
		Play(SILENCE,10);
		Play(_DO_5,250);
		Play(SILENCE,10);
		Play(_RE_5,250);
		Play(SILENCE,10);
		Play(_DO_5,250);
		Play(SILENCE,10);
		Play(_LA_S,750);
		Play(SILENCE,750);
		//
		Play(_RE_5,250);
		Play(SILENCE,10);
		Play(_SOL_5,250);
		Play(SILENCE,10);
		Play(_LA_5,250);
		Play(SILENCE,10);
		Play(_LA_S_5,250);
		Play(SILENCE,10);
		Play(_LA_5,500);
		Play(SILENCE,10);
		Play(_LA_5,250);
		Play(SILENCE,10);
		Play(_SOL_5,250);
		Play(SILENCE,10);
		Play(_LA_5,250);
		Play(SILENCE,10);
		Play(_SOL_5,250);
		Play(SILENCE,10);
		
		Play(_RE,250);
		Play(SILENCE,10);
		Play(_FA,250);
		Play(SILENCE,10);
		Play(_SOL,750);
		Play(SILENCE,10);
		Play(SILENCE,1000);
    }
}
void ConfigIO()
{
	cli();
	DDRB |= (1<<DDB3);
	TCCR0 = (1<<WGM01)|(0<<WGM00)|(0<<COM01)|(1<<COM00);
	TCCR0|= (0<<CS02)|(1<<CS01)|(0<<CS00); //PREESCALA 8
	OCR0 = _DO;
	TIMSK = (1<<OCIE0);
	sei();
}

void Play(uint8_t note, uint16_t duration)
{
	
	if (note == SILENCE)
	{
		DisableSound();
		for(uint16_t i = 0;i<duration;i++)
		{
			_delay_ms(1);
		}
	}
	else
	{
		EnableSound();
		pulsesCounter = 0; //limpiar contador
		
		float fNote  = 1000000.0/(float)(2*N*(1+note));//obtener frecuencia de la nota
		float tNote = (1/fNote)*1000; //periodo en mili segundos
		uint16_t pulsesAmaunt = (duration/tNote)*2; //cantidad de pulsos necesarios para lograr la duración de la nota
		
		
		cli();
		OCR0 = note; //cargar valor de comparación
		sei();//activar interrupciones
		
		do
		{
			
		} while (pulsesCounter<pulsesAmaunt);
	}
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