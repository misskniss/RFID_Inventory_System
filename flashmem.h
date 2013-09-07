#ifndef __FLASHMEM_H
#define __FLASHMEM_H

int Flash_Init(void);
uint8_t Flashmem_ID(void);
int slave_up(void);
int slave_down(void);
uint8_t Flash_Read(void);
int Flash_Write(uint8_t byte);
int Flash_Test_Write(void);
int Flash_Byte_Write(uint8_t *bytes, uint8_t addr);
uint8_t Flash_Read_Bytes(unsigned int, uint8_t, uint8_t, uint8_t);
uint8_t Flash_Test_Read(void);
void Flash_String_Push(uint8_t *s);
void Flash_Delete_Sector(void);
void Flash_Delete_Page(void);

#endif /*__FLASHMEM_H  */



