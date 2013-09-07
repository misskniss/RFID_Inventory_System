/* file: flashme.c  
 * Author: ykk
 */
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include "flashmem.h"
#include "uart1.h"




/*      GENERAL INFO     
 *	CS_SS = 0 				Enable FLash Device
 *	DI_MOSI = xxxx			Send instruction from ATmega to W25Q
 *	DO_MISO = xxxx 			Get data from W25Q 
 *	while(!(SPSR & 0x80));  Do nothing until SPIF interupt flag is set	
 *	
 *	General Instruction format:
 *	[CS_SS low]->[Instrction Code]->[24bit/6byte Address]->[data]->[CS_SS high]
 *
 *
 */

//TODO: Functions should pass ints not array pointers


int Flash_Init(void){
	DDRB = (1<<DDB4)|(1<<DDB5)|(1<<DDB7);
	PORTB = (1<<DDB4);
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	return 0;
}

uint8_t Flashmem_ID(void){
	uint8_t dev_ID = 0;
	//uint8_t man_ID = 0;
	
	slave_down();
	_delay_ms(1);
	Flash_Write(0x90);
	Flash_Write(0x00);
	Flash_Write(0x00);
	Flash_Write(0x01);
	Flash_Write(0x00);
	dev_ID = SPDR;							
	//man_ID = SPDR;							
	slave_up();
	return dev_ID;
	//return man_ID;

}

int slave_up(void){
	PORTB = PORTB | (1<<PB4);
	return 0;
}

int slave_down(void){
	PORTB = PORTB & ~(1<<PB4);    			
	return 0;
}


int Flash_Write(uint8_t	byte){
	SPDR = byte;
	while (!(SPSR & 0x80));					 //do nothing
	return 0;
}

int Flash_Test_Write(void){
	slave_down();
	Flash_Write(0x06);
	slave_up();
	_delay_ms(1);
	slave_down();
	_delay_ms(1);
	Flash_Write(0x02);
	Flash_Write(0x07);
	Flash_Write(0x00);
	Flash_Write(0x00);
	Flash_String_Push("I Drank What? -Socrates");
	slave_up();
	return 0;
}

void Flash_String_Push(uint8_t *s){
		UART1_Flush();
        while (*s) {                   		//point to the string array
			//UART1_TX(*s);
           	Flash_Write(*s);                	//transmit current element
           	s++;                        		//increment element, rinse, repeat until dry.
        }
}

int Flash_Byte_Write(uint8_t *bytes, uint8_t addr){
	uint8_t index;
	uint8_t buf[8];
	for(index=0;index<5; index++){
	UART1_Print(itoa(*(bytes+index), buf, 16));
	}
	slave_down();
	Flash_Write(0x06);
	slave_up();
	_delay_ms(1);
	slave_down();
	_delay_ms(1);
	Flash_Write(0x02);
	Flash_Write(addr);
	Flash_Write(0x00);
	Flash_Write(0x00);
	for(index=0; index<5; index++){
	Flash_Write(*(bytes+index));
	}
	slave_up();
	_delay_ms(1);
	return 0;
}

uint8_t Flash_Read(void){
	while(!(SPSR & 0x80)); 					//do nothing while SPI Int Flag not set
	return SPDR;
}

uint8_t Flash_Read_Bytes(unsigned int num_bytes, uint8_t byte1, uint8_t byte2, uint8_t byte3){
	uint8_t buf[8];
	uint8_t index;
	while(!(SPSR & 0x80)); 				
	slave_down();
	_delay_ms(1);
	Flash_Write(0x03);
	Flash_Write(byte1);
	Flash_Write(byte2);
	Flash_Write(byte3);
	int count = 0;
	uint8_t letters[num_bytes];
	while(count != (num_bytes + 1)){
		_delay_ms(1);
		Flash_Write(0x00);
    	letters[count] = SPDR;
		//UART1_TX(letters[count]);
		count++;	
	}
	slave_up();
	_delay_ms(1);
	uint8_t *letts = letters;
	//UART1_Print(letts);
	for(index=0; index<5; index++){
		UART1_Print(itoa(*(letts+index), buf, 16));
	}
	UART1_Flush();
	return 0;
}
uint8_t Flash_Test_Read(void){
	uint8_t num_bytes = 4;
	while(!(SPSR & 0x80)); 				
	slave_down();
	Flash_Write(0x03);
	Flash_Write(0x04);
	Flash_Write(0x00);
	Flash_Write(0x00);
	int count = 0;
	uint8_t letters[num_bytes];
	while(count != (num_bytes+1)){
		Flash_Write(0x00);
    	letters[count] = SPDR;
		count++;	
	
	}
	slave_up();
	_delay_ms(1);
	uint8_t *letts = letters;
	UART1_Print(letts);
	return SPDR;							// may not make sense to return anything here. Change this. 
}

void Flash_Delete_Sector(void){
//TODO

}

void Flash_Delete_Page(void){
//TODO

}
