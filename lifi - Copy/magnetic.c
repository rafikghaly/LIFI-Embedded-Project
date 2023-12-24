#include"tm4c123gh6pm.h"
#include"DIO.h"
#include"stdint.h"
//
#include"stdio.h"
#include"DIO.h"
#include"magnetic.h"
//
//
//
void magneticInit(void){
DIO_Init(1);
GPIO_PORTA_PUR_R|=0x40;
GPIO_PORTA_DIR_R|=0x00;
GPIO_PORTA_DEN_R|=0x40;
// 
}
//
uint8_t get_magnetic_status(){
return (GPIO_PORTA_DATA_R&(1<<6))>>6;

}
//
//
