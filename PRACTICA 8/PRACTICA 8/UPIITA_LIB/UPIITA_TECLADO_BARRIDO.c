/*
 * UPIITA_TECLADO_BARRIDO.c
 *
 * Created: 23/03/2023 07:19:33 p.m.
 *  Author: Alan
 */ 
#include "UPIITA_TECLADO_BARRIDO.h"

char LEE_TECLADO()
{
	char VALOR_TECLADO=' ';
	switch(PORTB)
	{
		case COL1:
		switch(PINB&0X0F)
		{
			case FIL1: VALOR_TECLADO='1'; break;//0X0E
			case FIL2: VALOR_TECLADO='2'; break;//0X0D:
			case FIL3: VALOR_TECLADO='3'; break;//0X0B
			case FIL4: VALOR_TECLADO='A'; break;//0X07
		}
		break;
		
		case COL2:
		switch(PINB&0X0F)
		{
			case FIL1: VALOR_TECLADO='4'; break;
			case FIL2: VALOR_TECLADO='5'; break;
			case FIL3: VALOR_TECLADO='6'; break;
			case FIL4: VALOR_TECLADO='B'; break;
		}
		break;
		
		case COL3:
		switch(PINB&0X0F)
		{
			case FIL1: VALOR_TECLADO='7'; break;
			case FIL2: VALOR_TECLADO='8'; break;
			case FIL3: VALOR_TECLADO='9'; break;
			case FIL4: VALOR_TECLADO='C'; break;
		}
		break;
		
		case COL4:
		switch(PINB&0X0F)
		{
			case FIL1: VALOR_TECLADO='*'; break;
			case FIL2: VALOR_TECLADO='0'; break;
			case FIL3: VALOR_TECLADO='#'; break;
			case FIL4: VALOR_TECLADO='D'; break;
		}
	break;
	}
	
	return VALOR_TECLADO;
}

void BARRE_TECLADO()
{
	switch(PORTB)
	{
		case COL1: PORTB=COL2; break;
		case COL2: PORTB=COL3; break;
		case COL3: PORTB=COL4; break;
		//case COL4: PORTD=COL1; break;
		default: PORTB=COL1;
	}
}
