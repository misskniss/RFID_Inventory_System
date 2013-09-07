
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uart2.h"
#include "uart1.h"
#include "rfid.h"
#include "defines.h"

uint8_t buf[8] = {0};
uint8_t err = -1;
uint8_t family[5] = {0};
uint8_t bytes_read[5] = {0};
uint8_t identity[5] = {0};

void Reset_Tag(void){
	err = -1;
	while(err != 1){
		UART2_Flush();
		UART2_Print("!RW");
		_delay_ms(1);
		UART2_TX(0x06);
		err = UART2_RX();
	}
}//

uint8_t * Read_RFID(uint8_t addr){
	uint8_t static byte1, byte2, byte3, byte4;
	err = -1;
	while(err != 1){
		UART2_Print("!RW");
		_delay_ms(1);
		UART2_TX(0x01);
		_delay_ms(1);
		UART2_TX(addr);
		err = UART2_RX();
		byte1 = UART2_RX();
		byte2 = UART2_RX();
		byte3 = UART2_RX();
		byte4 = UART2_RX();
		bytes_read[0] = byte1;
		bytes_read[1] = byte2;
		bytes_read[2] = byte3;
		bytes_read[3] = byte4;
			UART1_Flush();
	}
		return &bytes_read[0];
}//

uint8_t * Read_Serial_RFID(void){
	uint8_t static byte1, byte2, byte3, byte4;
	err = -1;
	while(err != 1){
		UART2_Print("!RW");
		_delay_ms(1);
		UART2_TX(0x01);
		_delay_ms(1);
		UART2_TX(32);
		_delay_ms(1);
		err = UART2_RX();
		byte1 = UART2_RX();
		byte2 = UART2_RX();
		byte3 = UART2_RX();
		byte4 = UART2_RX();
		identity[0] = byte1;
		identity[1] = byte2;
		identity[2] = byte3;
		identity[3] = byte4;
		identity[4] = 0;
			UART1_Flush();
	}
			return &identity[0];
}//

uint8_t * Read_Family_RFID(void){
	uint8_t static byte1, byte2, byte3, byte4;
	err = -1;
	while(err != 1){
		UART2_Print("!RW");
		_delay_ms(1);
		UART2_TX(0x01);
		_delay_ms(1);
		UART2_TX(33);
		_delay_ms(1);
		err = UART2_RX();
		byte1 = UART2_RX();
		byte2 = UART2_RX();
		byte3 = UART2_RX();
		byte4 = UART2_RX();
		family[0] = byte1;
		family[1] = byte2;
		family[2] = byte3;
		family[3] = byte4;
		family[4] = 0;
			UART1_Flush();
	}
	return &family[0];
}//

void Write_RFID(uint8_t start_addr, uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4){
	uint8_t buf[8];
	UART1_Print("\nWriting to tag...");
	UART1_Print(itoa(byte1, buf, 16));
	UART1_Print(itoa(byte2, buf, 16));
	UART1_Print(itoa(byte3, buf, 16));
	UART1_Print(itoa(byte4, buf, 16));
	
	uint8_t static err = -1;
	while(err != 1){
		UART2_Print("!RW");
		UART2_Flush();
		_delay_ms(1);
		UART2_TX(0x02);
		UART2_Flush();
		_delay_ms(1);
		UART2_TX(start_addr);
		UART2_Flush();
		_delay_ms(1);
		UART2_TX(byte1);
		UART2_Flush();
		_delay_ms(1);
		UART2_TX(byte2);
		UART2_Flush();
		_delay_ms(1);
		UART2_TX(byte3);
		UART2_Flush();
		_delay_ms(1);
		UART2_TX(byte4);
		UART2_Flush();
		_delay_ms(1);
		UART2_Flush();
		err = UART2_RX();
		UART2_Flush();

		//UART1_Print(itoa(err, buf, 16));
	}	
}//

void Read_Data_RFID(uint8_t start_addr, uint8_t num_bytes){
	;
}//


