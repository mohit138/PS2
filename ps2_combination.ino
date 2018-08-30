#include <PS2X_lib.h>

#include <SPI.h>
#define SerialPS2 Serial3
//#define Newcircuit


//-----------------------------------------------DELAYTIME_FOR_PS2------------------------- 
//#define PS3
#define basePS2_Y 128.0
#define wirelessdelay 0
#ifdef PS3
#define wirelessdelay 50 
#define basePS2_Y 127.0
#endif


/* Structs/Variables for driving */
      

//---------------------------------PINS------------------------------------------------------------
//------------------------------END-----------------------------------------------------------------------

//----------------------------------------PID-------------------------------------------------------------

//------------------------------PS2---------------------------------------------------------------------



float distAnalogleft,distAnalogright;


#define PS2_DAT        50  //14    
#define PS2_CMD        51  //15
#define PS2_SEL        31  //16
#define PS2_CLK        52  //17

#ifdef Newcircuit
#define PS2_SEL        6
#endif
/******************************************************************
 * select modes of PS2 controller:
 *   - pressures = analog reading of push-butttons 
 *   - rumble    = motor rumbling
 * uncomment 1 of the lines for each mode selection
 ******************************************************************/
//#define pressures   true
//#define pressures   false
//#define rumble      true
//#define rumble      false

PS2X ps2x; // create PS2 Controller Class

double xSquare_leftdistance=0,ySquare_leftdistance=0,xSquare_rightdistance=0,ySquare_rightdistance=0,xCircle_leftdistance=0,yCircle_leftdistance=0,xCircle_rightdistance=0,yCircle_rightdistance=0;
double LeftAnalogTheta=0,RightAnalogTheta=0;//w1=0,w2=0;
float LeftAnalogDistance=0,RightAnalogDistance=0;//r1=0,r2=0; //r1-Leftanalogdist w1-Leftanalogtheta


int error = 0;
byte type = 0;
byte vibrate = 0;

//---------------------------------------------END------------------------------------------------------------------------------------------------

const float rad = 1;
const float pi = 3.14159;




void setup() {                                                                                           
  Serial.begin(9600);
  SerialPS2.begin(9600);
  initPS2();
}
int frontpressed=0,backpressed=0;

void loop() {  
      getPS2value();    
      //scalePS2value();
      PS2executePressed();      
       
} 

 
