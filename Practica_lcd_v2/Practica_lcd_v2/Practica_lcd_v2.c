/*
 * practica_lcd.c
 *
 * Created: 13/03/2023 10:59:52 a. m.
 * Author : ing_0
 */ 


#define F_CPU 1000000
#define WAIT_TIME 3000
#define WAIT_CMD 500

#define LCD_PUERTO PORTD
#define LCD_RS PD2
#define  LCD_E PD3

#include <avr/io.h>
#include <util/delay.h>
#include "UPIITA_LIB/UPIITA_LCD_LIB.h"
//#include "UPIITA_LIB/Lcd4bits.h"

int main(void)
{
	DDRD = 0XFF;
	DDRA = 0xff;
	PORTD = 0X00;
	LCD_INICIALIZA();
	
	while(1)
	{
		PORTA = 0x02;
		LIMPIA_LCD();
		//APAGAR_CURSOR();
		_delay_ms(10);
		REGRESO_CASA();
		_delay_ms(10);
		POS_LINEA1(0);
		ENVIA_CADENA("Chávez Vázquez");
		_delay_ms(10);
		POS_LINEA2(1);
		ENVIA_CADENA("2012090113");
		_delay_ms(WAIT_TIME);
		
		LIMPIA_LCD();
		_delay_ms(10);
		REGRESO_CASA();
		
		CAR_ESP0();
		_delay_ms(5);
		CAR_ESP1();
		_delay_ms(5);
		CAR_ESP2();
		_delay_ms(5);
		CAR_ESP3();
		_delay_ms(5);
		CAR_ESP4();
		_delay_ms(5);
		CAR_ESP5();
		_delay_ms(5);
		CAR_ESP6();
		_delay_ms(5);
		CAR_ESP7();
		
		for(int i = 0; i<8; i++)
		{
			POS_LINEA1(i);
			ENVIA_DATO(i);
			_delay_ms(5);
		}
		//ENVIA_DATO(0);
		PORTA = 0X00;
		_delay_ms(WAIT_TIME);
		
		//TODO:: Please write your application code
	}
}
