/*FILE: uart.c
 *Author: YKK
 * 
 * This file handles the set up of the first UART serial comm
 *
 */

#include <avr/io.h>
#include "uart1.h"

#define F_CPU 1000000//MHz

int UART1_Init(void){
		UBRR0H = 0;
		UBRR0L = 0x0c;
		UCSR0A = 32 | (1<<U2X1);
        UCSR0B = (1 << RXEN0) | (1 << TXEN0);
        UCSR0C = (0 << USBS0) | (3 << UCSZ00);
		return 0;
    }

//unsigned char UART1_RX(void){
uint8_t UART1_RX(void){
        while(!(UCSR0A & ( 1 << RXC0 ) ))
            ;
        return UDR0;
    }

//void UART1_TX(unsigned char letter){
void UART1_TX(uint8_t letter){
        while( !(UCSR0A & (1 << UDRE0)) )
            ;
        UDR0 = letter;
		UCSR0A = UCSR0A | (1<<TXC0);
    }


/*point to the string array
 * transmit current element
 * then increment, rinse, repeat. 
 */
//void UART1_Print(char *s){
void UART1_Print(uint8_t *s){
        while (*s) {                   
           UART1_TX(*s);               
           s++;                      
        }
}

void UART1_Flush(void){
	uint8_t dummy;
	while(UCSR0A & (1 << RXC0)) dummy = UDR0;
}

void UART1_Send_Com(int n){
	
    while( !(UCSR0A & (1 << UDRE0)) )
            ;
	UDR0 = n;
	}
