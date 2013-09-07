#ifndef __UART2_H
#define __UART2_H

int UART2_Init(void);
//unsigned char UART2_RX(void);
uint8_t UART2_RX(void);
void UART2_TX(uint8_t letter);
void UART2_Print(uint8_t *s);
void UART2_Send_Com(int n);
void UART2_Flush(void);


#endif /*__UART2_H  */
