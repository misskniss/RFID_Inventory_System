#ifndef __RFID_H
#define __RFID_H

void Reset_Tag(void);
uint8_t * Read_RFID(uint8_t addr);
uint8_t * Read_Serial_RFID(void);
uint8_t * Read_Family_RFID(void);
void Read_Data_RFID(uint8_t start_addr, uint8_t num_bytes);
void Write_RFID(uint8_t start_addr, uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4);

#endif /*__RFID_H  */
