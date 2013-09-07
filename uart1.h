#ifndef __UART1_H
#define __UART1_H

int UART1_Init(void);
//unsigned char UART1_RX(void);
uint8_t UART1_RX(void);
//void UART1_TX(unsigned char letter);
void UART1_TX(uint8_t letter);
//void UART1_Print(char *s);
void UART1_Print(uint8_t *s);
void UART1_Send_Com(int n);
void UART1_Flush(void);


#endif /*__UART1_H  */
