/*
 * practica4_interrupEXT.c
 *
 * Created: 27/03/2023 08:16:03 a. m.
 * Author : ing_0
 */ 

#define F_CPU 1000000UL
#define WAIT_LED 200
#define LEDS_PORT PORTA
#define LEDS_DDR DDRA

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LIB_UPIITA/UPIITA_LCD_LIB.h"

////////////////////////////////////////////////////////////////////////////////
//---------------------------funciones prototipo--------------------------------
void LedSequence(); 

////////////////////////////////////////////////////////////////////////////////
//------------------------Declaración de variables globales---------------------

uint8_t output = 0x01;

////////////////////////////////////////////////////////////////////////////////
//---------------------------Vectores de interrupción-------------------------
ISR(INT0_vect){
	//mostrar nombre en la LCD
	LIMPIA_LCD();
	REGRESO_CASA();
	ENVIA_CADENA("Chávez Vázquez");
	POS_LINEA1(0);
	ENVIA_CADENA("Alan Baruch");
}

ISR(INT1_vect){
	//MOSTRAR 4 CARACTERES ESPECIALES EN LA LCD
	LIMPIA_LCD();
	REGRESO_CASA();
	for(int i = 0; i<4; i++)
	{
		ENVIA_DATO(i);
	}
}

ISR(INT2_vect){
	//MOSTRAR ULTIMOS 4 CARACTERES SPECIALES EN LCD
		LIMPIA_LCD();
		REGRESO_CASA();
		for(int i = 4; i<8; i++)
		{
			ENVIA_DATO(i);
		}
}
////////////////////////////////////////////////////////////////////////////////


void ConfigIO()
{
	cli();
	LEDS_DDR = 0xFF;//SALIDAS PARA LEDS
	LEDS_PORT = 0X01;// VALOR INICIAL
	
	DDRC = 0XFF; //PUERTO DE LA LCD
	PORTC = 0X00;
	
	DDRD = 0b11110011;// entradas PD2(INT0), PD3(INT1)
	PORTD = 0XFF; //PULLUP ENABLED
	
	DDRB = 0b11111011;//entrada pb2(int2)
	PORTB = 0b00000100;//pullup enabled
	
	//-----------CONFIGURAR INTERRUPCIONES---------
	GICR|= (1<<INT0)|(1<<INT1)|(1<<INT2);// ACTIVADAS INTERRUPCIONES EXTERNAS 0,1Y2
	MCUCR |= (1<<ISC01)|(0<<ISC00); //INT0 POR FRANCO DE BAJADA
	MCUCR |= (1<<ISC11)|(0<<ISC10);//INT1 POR FRANCO DE BAJADA
	MCUCSR |= (0<<ISC2); //INT2 POR FRANCO DE BAJADA
	sei();
}


int main(void)
{
	ConfigIO(); //CONFIGURAR ENTRADAS Y SALIDAS
	LCD_INICIALIZA(); //INICIALIZAR LCD
	CARGAR_CAR_ESP();
	
    /* Replace with your application code */
    while (1) 
    {
		LedSequence();
    }
}


////////////////////////////////////////////////////////////////////////////////
//--------------------------Funciones del programa------------------------------

void LedSequence()
{
	for(uint8_t j=0; j<7; j++)
	{
		_delay_ms(WAIT_LED);
		output = (output<<1);
		LEDS_PORT = output;
	}
	
	for(uint8_t j=0; j<7; j++)
	{
		_delay_ms(WAIT_LED);
		output = (output>>1);
		LEDS_PORT = output;
	}
}

