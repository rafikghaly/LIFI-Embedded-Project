#include"tm4c123gh6pm.h"
#include"DIO.h"
#include"stdint.h"
//
#include"stdio.h"
#include"DIO.h"
#include"fume.h"
#include"ultrasonicV1.h"
#include"magnetic.h"
uint32_t time; /*stores pulse on time */
uint32_t distance; /* stores measured distance value */
char mesg[20];  /* string format of distance value */
uint8_t status;

_Bool FlagU = 0;
_Bool FlagF = 0;
_Bool FlagM = 0;
int TimeU = 0;
int TimeM = 0;
int TimeF = 0;


int main(void)
{


//For Fume
FumeInit();

//For Magnetic
magneticInit();

//For UltraSonic
Timer0ACapture_init();  /*initialize Timer0A in edge edge time */

//For Bluetooth
UART5_init(); /* initialize UART5 module to transmit data to computer */


while(1)
  {
   Bluetooth_Write_String("hi1");
   /////////////////////UltraSonic/////////////////////////////
   if(TimeU ==0)
   {
  time = Measure_distance(); /* take pulse duration measurement */ 
  distance = (time*10625 )/10000000; /* convert pulse duration into distance */
  //printf("distance %d \n",distance);
  if (distance<20)
  {
    FlagU = 1;
    //Eb3at Laser
    //delay
    TimeU = 5;
  }
   }
   else 
   { 
    sprintf(mesg, "\r\nTimeU = %d", TimeU);
    Bluetooth_Write_String(mesg);
    Bluetooth_Write_String("\n");
    TimeU--;  
   }
  //sprintf(mesg, "\r\nDistance = %d cm", distance); /*convert float type distance data into string */
  //Bluetooth_Write_String(mesg);
  //Bluetooth_Write_String("\n");
  //printstring(mesg); /*transmit data to Mobile */
  //////////////////////////////////////////////////
  
  
  Delay(2000);
  /////////////////////Fume/////////////////////////////
  //printf("Fume raw%d\n",ADC0_SSFIFO3_R);
  if (TimeF ==0){
  //printf("Fume Raw %d",ADC0_SSFIFO3_R);
  //sprintf(mesg, "\r\nFume Raw = %d", ADC0_SSFIFO3_R); /*convert float type distance data into string */
  //Bluetooth_Write_String(mesg);
  //Bluetooth_Write_String("\n");
  if(ADC0_SSFIFO3_R>850)
  {
  //printf("Smoke Detected");
    FlagF = 1;
    //Eb3at Laser
    //delay
    TimeF = 10;
  //Bluetooth_Write_String("Smoke Detected");
  //Bluetooth_Write_String("\n");
   
  }
  }
  else
  {
    sprintf(mesg, "\r\nTimeF = %d", TimeF);
    Bluetooth_Write_String(mesg);
    Bluetooth_Write_String("\n");
    TimeF--;
  }
  delay_ms(100);
  

  /////////////////////Magnetic/////////////////////////////
  if(TimeM==0){
  status = get_magnetic_status();
  //Magnetic on A6
  // Check the magnetic switch status
  if (status == 1) {
      // Door is closed
    //printf("Door is opened");
      FlagM = 1;
      //Eb3at Laser
      //delay
      TimeM = 5;
    //Bluetooth_Write_String("Door is opened");
    //Bluetooth_Write_String("\n");
   
  } else {
      // Door is open

    //printf("Door is closed; ");
    //Bluetooth_Write_String("Door is Closed");
    //Bluetooth_Write_String("\n");
  }

  }
  else 
  {
    sprintf(mesg, "\r\nTimeM = %d", TimeM);
    Bluetooth_Write_String(mesg);
    Bluetooth_Write_String("\n");
    TimeM--;
  }
  
  if(FlagF)
{
	FlagF = 0;
	Bluetooth_Write_String("Smoke Detected");
        Bluetooth_Write_String("\n");
}
if(FlagM && (FlagF ==0))
{
	FlagM = 0;
	Bluetooth_Write_String("Door is opened");
        Bluetooth_Write_String("\n");
}
if (FlagU && (FlagF == 0) && (FlagM == 0))
{
	FlagU= 0;
	sprintf(mesg, "\r\nDistance = %d cm", distance); /*convert float type distance data into string */
        Bluetooth_Write_String(mesg);
        Bluetooth_Write_String("\n");
}
  
  
  
} 
}