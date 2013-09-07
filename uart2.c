/*FILE: uart2.c (Final Project RFID Inventory System)
 *Author: YKK  - Jen Kniss
 * 
 * This file handles the set up of the second UART serial comm
 *
 */

#include <avr/io.h>
#include "uart2.h"

#define F_CPU 1000000//MHz

/* UBRRxH and UBRRxL set the baud rate 
 * UCSRxA sets the TX complete, RX complete, U2X and other bits - inits to zero here
 * UCSRxB sets enables the TX, RX when set to 1
 * UCSRBxC sets the frame rate and stop bit
 */

int UART2_Init(void){
		UBRR1H = 0;
		UBRR1L = 0x0c;
		UCSR1A = 32 | (1<<U2X1);
        UCSR1B = (1 << RXEN1) | (1 << TXEN1);
        UCSR1C = (0 << USBS1) | (3 << UCSZ10);
		return 0;
    }

uint8_t UART2_RX(void){
        while(!(UCSR1A & ( 1 << RXC1 ) ))
            ;
        //return UDR1;
    	uint8_t byte1 = UDR1;
		UCSR0A = UCSR1A | (1<<RXC1);
		return byte1;
    }

void UART2_TX(uint8_t letter){
        while( !(UCSR1A & (1 << UDRE1)) )
            ;
        UDR1 = letter;
		UCSR1A = UCSR1A | (1<<TXC1);
    }

/*point to the string array,
 * transmit current element,
 * increment element, rinse, repeat.
 */
void UART2_Print(uint8_t *s){
        while (*s) {                   
           UART2_TX(*s);                
           s++;                        
        }
	}

void UART2_Flush(void){
	uint8_t dummy;
	while(UCSR1A & (1 << RXC1)) dummy = UDR1;
}

void UART2_Send_Com(int n){
    while( !(UCSR1A & (1 << UDRE1)) )
            ;
	UDR1 = n;
	}
