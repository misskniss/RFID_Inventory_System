/*
 *File main.c for final project.
 *Author Jkniss
 *
 */


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uart2.h"
#include "uart1.h"
#include "rfid.h"
#include "defines.h"
#include "flashmem.h"

int main(void){

	uint8_t sample[10] = "sneeches!";
	uint8_t *familytype;
	uint8_t *identification;
	uint8_t *read_bytes;
	const uint8_t str_size = strlen(sample);
	uint8_t mod_value = str_size % 4;
	uint8_t buf[8] = {0};
	uint8_t addrs, index, byte1, byte2, byte3, byte4;
	uint8_t rfid_address = 3;
	uint8_t flash_start_addr = 0x0b;
	int count;

	/* INITs & SET UP CALCULATIONS */	
	if(!(UART1_Init())){
		UART1_Print("\nUART 1 Initialized\n");
		UART1_Print(itoa(str_size, buf, 10));
		UART1_Print(" ");
		UART1_Print(itoa(mod_value, buf, 10));
		UART1_Print(" ");
		UART1_Print(itoa(str_size/4, buf, 10));
		UART1_Print(" ");
	}
	if(!(UART2_Init())){
		UART1_Print("\nUART 2 Initialized\n");
	}
	if(!(Flash_Init())){
		UART1_Print("\nFlash Memory Inititalized");
		UART1_Print("Flash memory ID: ");
		UART1_Print(itoa(Flashmem_ID(), buf, 16));
		UART1_Print("\r\n");
	}else{
		UART1_Print("\nProblem initializing flash...");
	}
	
	if(str_size % 4 != 0){
		addrs = ((str_size/4) + 1);
		UART1_Print("Addrs:");
		UART1_Print(itoa(addrs, buf, 10));
		UART1_Print("\n");
	}
	else{
		addrs = str_size/4;
		UART1_Print("Addrs:");
		UART1_Print(itoa(addrs, buf, 10));
		UART1_Print("\n");
	}

	rfid_address = 9;
	while(1){
		UART1_Print("\r\n#### START ####");
		
		/* GET FAMILY TYPE */
		UART1_Print("\r\nRFID Tag Family Is Type:");
		familytype = Read_Family_RFID();
		//for(index = 0; index < strlen(familytype); index++){
		for(index = 0; index < 3; index++){
			UART1_Print(itoa(*(familytype+index), buf, 16));
		}
		UART1_Flush();
		
		/* GET SERIAL NUMBER */
		UART1_Print("\r\nRFID Tag Serial #:");
		identification = Read_Serial_RFID();
		for(index = 0; index < strlen(identification); index++){
			UART1_Print(itoa(*(identification+index), buf, 16));
		}
		UART1_Flush();

		/* WRITE STRING */
		Write_RFID(rfid_address, sample[0], sample[1], sample[2], sample[3]);
		_delay_ms(5);
		
		/* READ ADDRESS */
		UART1_Print("\r\nReading RFID address ");
		UART1_Print(itoa(rfid_address, buf, 10));
		UART1_Print("...");
		read_bytes = Read_RFID(rfid_address);
		for(index = 0; index < strlen(read_bytes); index++){
			UART1_Print(itoa(*(read_bytes+index), buf, 16));
		}
		read_bytes = Read_RFID(rfid_address);
		//for(index = 0; index < strlen(read_bytes); index++){
		//	UART1_Print(itoa(*(read_bytes+index), buf, 16));
		//}
		UART1_Flush();
		
		/* STORING IDENTIFICATION */
		UART1_Print("\r\nWriting to flash... ");
		UART1_Flush();
		_delay_ms(1);
		//Flash_Test_Write();
		Flash_Byte_Write(&identification[0], flash_start_addr);
		UART1_Flush();
		UART1_Print("\r\nReading flash...: ");
		UART1_Flush();
		_delay_ms(1);
		Flash_Read_Bytes(10, flash_start_addr,0x00,0x00);
		_delay_ms(1);
		UART1_Print("\r\n#### DONE ####\r\n");

		/* CLEAN UP */
		Reset_Tag();
		_delay_ms(5);
		UART1_Flush();
		free(read_bytes);
		free(familytype);
		free(identification);
	}
	return 0;


}
	//address = 7;
	//index = 0;
	/*Adrian: this is the portion of code I WANT to use. The stuff
	 * in the while loop below is how I know the write call is only 
	 * working one at a time. 
	 *
	 * for(count = 0; count < addrs; count++){
		UART1_Print("\n");
		UART1_Print(itoa(sample[index], buf, 16));
		UART1_Print("\n");
		UART1_Print(itoa(sample[index+1], buf, 16));
		UART1_Print("\n");
		UART1_Print(itoa(sample[index+2], buf, 16));
		UART1_Print("\n");
		UART1_Print(itoa(sample[index+3], buf, 16));
		UART1_Print("\n");
		byte1 = sample[index];
		byte2 = sample[index + 1];
		byte3 = sample[index + 2];
		byte4 = sample[index + 3];
		Write_RFID(address, byte1, byte2, byte3, byte4);
		UART1_Flush();
		UART2_Flush();
		UART1_Print("Write addr:");
		UART1_Print(itoa(address, buf, 10));
		_delay_ms(1);
		UART1_Print("\r\nReading address :");
		UART1_Flush();
		UART2_Flush();
		Read_RFID(address);
		address++;
		index += 4;
	}*/

