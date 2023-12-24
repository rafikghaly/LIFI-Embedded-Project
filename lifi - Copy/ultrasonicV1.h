
#include"stdint.h"

uint32_t Measure_distance(void);
void Timer0ACapture_init(void);
void Delay_MicroSecond(int time);
void UART5_init(void);
void UART5_Transmitter(unsigned char data);
void printstring(char *str);
void Delay(unsigned long counter);
void Bluetooth_Write(unsigned char data); 
void Bluetooth_Write_String(char *str);
void delay_ms(int delay);
