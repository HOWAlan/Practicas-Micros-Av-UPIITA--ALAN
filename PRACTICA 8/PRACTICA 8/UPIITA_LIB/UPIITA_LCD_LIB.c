/*
 * UPIITA_LCD_LIB.c
 *
 * Created: 27/03/2023 08:58:36 a. m.
 *  Author: ing_0
 */ 
#define F_CPU 1000000
#include "UPIITA_LCD_LIB.h"

//uint8_t espCarAlan1[7] = {0x0e,0x1f,0x15,0x1f,0x1f,0x1f,0x0a};
//uint8_t espCarAlan2[7] = {0x1F,0x15,0x15,0x1F,0x15,0x15,0x1F};
//uint8_t espCarAlan3[7] = {0x11,0x11,0x1B,0x1F,0x1F,9x1F,0x0E};
//uint8_t espCarAlan4[7] = {0x11,0x15,0x0A,0x1F,0x15,0x15,0x00};

void CAR_ESP0(){
	ENVIA_CMD(0X40);
	_delay_ms(1);
	ENVIA_DATO(0b00011111);
	_delay_ms(1);
	ENVIA_DATO(0b00010101);
	_delay_ms(1);
	ENVIA_DATO(0b00010101);
	_delay_ms(1);
	ENVIA_DATO(0b00011111);
	_delay_ms(1);
	ENVIA_DATO(0b00001010);
	_delay_ms(1);
	ENVIA_DATO(0b00010101);
	_delay_ms(1);
	ENVIA_DATO(0b00011111);
	_delay_ms(1);
	ENVIA_DATO(0b00000000);
	_delay_ms(1);
}

void CAR_ESP1()
{
	ENVIA_CMD(0X48);
	_delay_ms(1);
	ENVIA_DATO(0b00000000);
	_delay_ms(1);
	ENVIA_DATO(0b00001010);
	_delay_ms(1);
	ENVIA_DATO(0b00011111);
	_delay_ms(1);
	ENVIA_DATO(0b00011111);
	_delay_ms(1);
	ENVIA_DATO(0b00011111);
	_delay_ms(1);
	ENVIA_DATO(0b00001110);
	_delay_ms(1);
	ENVIA_DATO(0b00000100);
	_delay_ms(1);
	ENVIA_DATO(0b00000000);
	_delay_ms(1);
}

void CAR_ESP2()
{
	ENVIA_CMD(0X50);
	_delay_ms(1);
	ENVIA_DATO(0b00000000);
	_delay_ms(1);
	ENVIA_DATO(0b00000011);
	_delay_ms(1);
	ENVIA_DATO(0b00000111);
	_delay_ms(1);
	ENVIA_DATO(0b00010110);
	_delay_ms(1);
	ENVIA_DATO(0b00001000);
	_delay_ms(1);
	ENVIA_DATO(0b00010100);
	_delay_ms(1);
	ENVIA_DATO(0b00000000);
	_delay_ms(1);
	ENVIA_DATO(0b00000000);
	_delay_ms(1);
}

void CAR_ESP3()
{
	ENVIA_CMD(0X58);
	_delay_ms(1);
	ENVIA_DATO(0b00000000);
	_delay_ms(1);
	ENVIA_DATO(0b00000000);
	_delay_ms(1);
	ENVIA_DATO(0b00000000);
	_delay_ms(1);
	ENVIA_DATO(0b00010100);
	_delay_ms(1);
	ENVIA_DATO(0b00001000);
	_delay_ms(1);
	ENVIA_DATO(0b00010110);
	_delay_ms(1);
	ENVIA_DATO(0b00000111);
	_delay_ms(1);
	ENVIA_DATO(0b00000011);
	_delay_ms(1);
}

void CAR_ESP4(void)
{
	uint8_t espCarAlan1[7] = {0x0e,0x1f,0x15,0x1f,0x1f,0x1f,0x0a};
	ENVIA_CMD(0X60);
	_delay_ms(1);
	for (int i= 0; i<7; i++)
	{
		ENVIA_DATO(espCarAlan1[i]);
		_delay_ms(1);
	}
}

void CAR_ESP5(void)
{
	uint8_t espCarAlan2[7] = {0x1F,0x15,0x15,0x1F,0x15,0x15,0x1F};
	ENVIA_CMD(0X68);
	_delay_ms(1);
	for (int i= 0; i<7; i++)
	{
		ENVIA_DATO(espCarAlan2[i]);
		_delay_ms(1);
	}
}

void CAR_ESP6(void)
{
	uint8_t espCarAlan3[7] = {0x11,0x11,0x1B,0x1F,0x1F,0x1F,0x0E};
	ENVIA_CMD(0X70);
	_delay_ms(1);
	for (int i= 0; i<7; i++)
	{
		ENVIA_DATO(espCarAlan3[i]);
		_delay_ms(1);
	}
}

void CAR_ESP7(void)
{
	uint8_t espCarAlan4[7] = {0x11,0x15,0x0A,0x1F,0x15,0x15,0x00};
	ENVIA_CMD(0X78);
	_delay_ms(1);
	for (int i= 0; i<7; i++)
	{
		ENVIA_DATO(espCarAlan4[i]);
		_delay_ms(1);
	}
}

void LCD_INICIALIZA()
{
	ENVIA_CMD(0x02);
	ENVIA_CMD(0x28); // 0010 1000 DL = 0 comunicacion de 4 bits N = 1 Pantalla de 2 lineas F = 0 Caracteres de 5x7 puntos
	ENVIA_CMD(0x0E); // D=1 Display ON Cursor OFF
	ENVIA_CMD(0x06); // I/D = 1 Incremento Automatico S=0
	ENVIA_CMD(0x01);  // Limpia LCD
	ENVIA_CMD(0X80);
}



void ENVIA_CMD(char dato)
{
	char cmd_enviar;
	
	cmd_enviar =	(dato & 0xF0);      // se envia el nibble alto
	LCD_PUERTO =  cmd_enviar;       // al puerto
	LCD_PUERTO &=~(1<<LCD_RS);  //  RS = 0
	LCD_PUERTO |= (1<<LCD_E);   //   E = 1
	_delay_ms(1);
	LCD_PUERTO &=~(1<<LCD_E);   //   E = 0
	_delay_ms(10);
	
	cmd_enviar=	((dato<<4) & 0xF0);  // Se envia el nibble bajo
	LCD_PUERTO =  cmd_enviar;        // al puerto
	LCD_PUERTO &=~(1<<LCD_RS);   //  RS = 0
	LCD_PUERTO |= (1<<LCD_E);    //   E = 1
	_delay_ms(1);
	LCD_PUERTO &=~(1<<LCD_E);    //    E = 0
	_delay_ms(10);
	return;
}

void ENVIA_DATO(char dato)
{
	char dto_enviar;
	
	dto_enviar=	(dato & 0xF0);      // se envia el nibble alto
	LCD_PUERTO  =  dto_enviar;       // al puerto
	LCD_PUERTO |= (1<<LCD_RS)|(1<<LCD_E);  //  RS = 1   E = 1
	_delay_ms(1);
	LCD_PUERTO &=~(1<<LCD_E);	//E=0
	LCD_PUERTO &=~(1<<LCD_RS);	//RS=0
	_delay_ms(10);
	
	dto_enviar=	((dato<<4) & 0xF0);  // Se envia el nibble bajo
	LCD_PUERTO =  dto_enviar;        // al puerto
	LCD_PUERTO |= (1<<LCD_RS)|(1<<LCD_E);  //  RS = 1   E = 1
	_delay_ms(1);
	LCD_PUERTO &=~(1<<LCD_E);	//E=0
	LCD_PUERTO &=~(1<<LCD_RS);	//RS=0
	_delay_ms(10);
	return;
}

void ENVIA_CADENA(char *dato)
{
	int i;
	for(i=0;dato[i]!='\0';i++)
	ENVIA_DATO(dato[i]);
}

void LIMPIA_LCD ()
{
	ENVIA_CMD (0x01);
}
//0000 0001

void REGRESO_CASA()
{
	ENVIA_CMD (0x02); //0000 0010
}

void CURSOR_DER()
{
	ENVIA_CMD (0x1C); //0001 1100
}

void CURSOR_DER_CORRE() //sin desplazar pantalla
{
	ENVIA_CMD (0x14);//0001 1100
}

void CURSOR_IZQ()
{
	ENVIA_CMD (0x18); // 0001 1000
}

void CURSOR_IZQ_CORRE() //sin desplazar pantalla
{
	ENVIA_CMD(0x10);
}

void PARPADEAR_CURSOR()
{
	ENVIA_CMD(0X0f);//0000 1111
}

void PARPADEAR_CURSOR_REC()
{
	ENVIA_CMD(0X0e);//00001110
}

void POS_LINEA1 (char posicion)
{
	char lineal = 0x80;
	posicion= posicion|lineal;
	ENVIA_CMD (posicion);
}


void POS_LINEA2 (char posicion)
{
	char linea2 = 0xC0;
	posicion= posicion|linea2;
	ENVIA_CMD (posicion);
}


void POS_LINEA3 (char posicion)
{
	char linea3 = 0x94;
	posicion= posicion | linea3;
	ENVIA_CMD (posicion);
}

void POS_LINEA4 (char posicion)
{
	char linea4 = 0xD4;
	posicion =posicion|linea4;
	ENVIA_CMD (posicion);
}


void animacion ()
{
	ENVIA_DATO (2);
	CURSOR_IZQ_CORRE();
	_delay_ms (50);
	ENVIA_DATO (3);
	CURSOR_IZQ_CORRE();
	_delay_ms (50);
}

void APAGAR_CURSOR()
{
	ENVIA_CMD(0X0C);
}

void LCD_HELLOWORLD()
{
	LIMPIA_LCD();
	_delay_ms(10);
	REGRESO_CASA();
	_delay_ms(10);
	POS_LINEA1(0);
	ENVIA_CADENA("Estoy vivo");
	_delay_ms(3000);
	LIMPIA_LCD();
	REGRESO_CASA();
}

void CARGAR_CAR_ESP()
{
	LIMPIA_LCD();
	_delay_ms(5);
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
	
	LIMPIA_LCD();
	_delay_ms(5);
	REGRESO_CASA();
}