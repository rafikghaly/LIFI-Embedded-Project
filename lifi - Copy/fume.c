

#include"DIO.h"
#include"stdint.h"
#include"bitwise_operation.h"
#include"tm4c123gh6pm.h"
#include"fume.h"
void delay_msF(int delay);
unsigned static char Temperature = 0;  
void FumeInit();

void FumeInit(){
uint32_t adc_data=0;
uint32_t val=0;
SYSCTL_RCGCGPIO_R=0x10;
//Temperature sensor connected CO GPIO pin PE2 (ANI 1)
GPIO_PORTE_DEN_R =0x0;
GPIO_PORTE_AMSEL_R = 0x3;
//Enable the clock for ADCO
SYSCTL_RCGCADC_R |= 0X01;
delay_ms(3);
ADC0_PC_R  |= 0x03; //250 Ksps
ADC0_EMUX_R  = 0xF000; //250 Ksps

//No Sequencer Priority
ADC0_SAC_R |= 0x04; //16x oversampling and then averaged

//No Voltage selection
ADC0_ACTSS_R = 0x00000008;   //Configure ADCO module tor sequencer3
ADC0_SSMUX3_R =0x01;         // ANI_1 (PE2) 19 assigned to InputO of SS3
ADC0_SSCTL3_R |= 0x02;      // Sample is end of sequence

}

void delay_msF(int delay){
NVIC_ST_CTRL_R=0x04;
NVIC_ST_RELOAD_R= delay*16000000-1;
NVIC_ST_CURRENT_R=0x0;
NVIC_ST_CTRL_R=0x05;
while((GET_BIT( &NVIC_ST_CTRL_R,16) ==0)) // count flagbit 16
{}
}


