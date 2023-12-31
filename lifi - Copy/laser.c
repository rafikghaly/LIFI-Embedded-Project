#include"DIO.h"
#include"stdint.h"
#include"bitwise_operation.h"
#include"tm4c123gh6pm.h"
#include"laser.h"


void laser_Init(void){
DIO_Init(2);
//GPIO_PORTB_PUR_R|=0x4;
GPIO_PORTB_DIR_R|=0x04;
GPIO_PORTB_DEN_R|=0x4;
// 
}
//
void set_laser_status(){
//SET_BIT(&GPIO_PORTB_DATA_R,2);
GPIO_PORTB_DATA_R|=0x4;

}

void clear_laser_status(){
//SET_BIT(&GPIO_PORTB_DATA_R,2);
  
CLEAR_BIT(&GPIO_PORTB_DATA_R,2);

}
