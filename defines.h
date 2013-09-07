/*file: inventory_defines.c
 *author YKK : Jen Kniss
 *
 */


#define ERR_OK 0x01
#define READ 0x01
#define WRITE 0x02
#define LOGIN 0x03
#define SET_PWD 0x04
#define PROTECT 0x05
#define RESET 0x06
#define LEGACY 0x0F

#define SERIAL_ID 32
#define DATA_START 3    //116 bytes available
#define FAMILY_ID 33
#define PROTECT_WORD 1
#define CONTROL_WORD 2
#define PASSWORD 0

#define DATA_ALL 116




/***** RFID Commands ******/ 
