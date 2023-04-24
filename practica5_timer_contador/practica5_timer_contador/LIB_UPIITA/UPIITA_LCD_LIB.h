/*
 * UPIITA_LCD_LIB.h
 *
 * Created: 27/03/2023 08:59:16 a. m.
 *  Author: ing_0
 */ 


#ifndef UPIITA_LCD_LIB_H_
#define UPIITA_LCD_LIB_H_
#include <avr/io.h>

#ifndef LCD_PUERTO
#define LCD_PUERTO PORTC
# warning "LCD_PUERTO not defined for LCD, used by default port PORTC"
#endif

#ifndef LCD_RS
#define LCD_RS PC2
#endif

#ifndef LCD_E
#define  LCD_E PC3
#endif

#include <util/delay.h>
#include <inttypes.h>
#include <stdint.h>

void LCD_INICIALIZA();
void LCD_HELLOWORLD();
void ENVIA_CMD(char dato);
void ENVIA_DATO(char dato);
void ENVIA_CADENA(char *dato);
void LIMPIA_LCD();
void CURSOR_DER();
void CURSOR_DER_CORRE();
void CURSOR_IZQ();
void CURSOR_IZQ_CORRE();
void PARPADEAR_CURSOR();
void PARPADEAR_CURSOR_REC();
void APAGAR_CURSOR();
void REGRESO_CASA();
void POS_LINEA1(char posicion);
void POS_LINEA2(char posicion);
void POS_LINEA3(char posicion);
void POS_LINEA4(char posicion);
void CAR_ESP0();
void CAR_ESP1();
void CAR_ESP2();
void CAR_ESP3();
void CAR_ESP4();
void CAR_ESP5();
void CAR_ESP6();
void CAR_ESP7();
void CARGAR_CAR_ESP();
#endif /* UPIITA_LCD_LIB_H_ */
