#include <PS2X_lib.h>
#include <EasyTransfer.h>
#include <SPI.h>

//#define SerialPS2 Serial
#define BluetoothSerial Serial2

#define PS3
#define basePS2_Y 128.0
#define wirelessdelay 0
#ifdef PS3
#define wirelessdelay 50 
#define basePS2_Y 127.0
#endif


EasyTransfer ET;
PS2X ps2x;


struct PS2_data{
 int32_t ps2data;
 uint8_t Rx;
 uint8_t Ry;
 uint8_t Lx;
 uint8_t Ly; 
};
PS2_data data;


double xSquare_leftdistance=0,ySquare_leftdistance=0,xSquare_rightdistance=0,ySquare_rightdistance=0,xCircle_leftdistance=0,yCircle_leftdistance=0,xCircle_rightdistance=0,yCircle_rightdistance=0;
double LeftAnalogTheta=0,RightAnalogTheta=0;
float LeftAnalogDistance=0,RightAnalogDistance=0;
const float rad = 1;
const float pi = 3.14159;
long int count=0;



void setup() {
  Serial.begin(9600);
  BluetoothSerial.begin(38400);
  ET.begin(details(data),&BluetoothSerial);
}

void loop() {
  ps2x.last_buttons=ps2x.buttons;
  if(ET.receiveData())
  {
       ps2x.buttons=data.ps2data;
       //Serial.println(ps2x.buttons);
  }
  
  scalePS2value();
  PS2executePressed();
  count++;
}



void PS2executePressed(){    

    if(count >3)         // put all released buttons functions  func in this loop)
     {                
          if(ps2x.ButtonReleased(PSB_R1))
         {
             Serial.println("R1");
             //r1Released();
         }
        
          if(ps2x.ButtonReleased(PSB_R2))
         {
           Serial.println("R2");
            //r2Released();
          }
          
          if(ps2x.ButtonReleased(PSB_L1))
         {
             Serial.println("L1");
             //r1Released();
         }
        
          if(ps2x.ButtonReleased(PSB_L2))
         {
           Serial.println("L2");
            //r2Released();
          }
      }
      
    if (ps2x.Button(PSB_PAD_UP))  //x refers to the array which will be in terms of 000x 0000 if switch corresponding to up is pressed and up refers to enum
    { 
         // upPressed();
          Serial.println("up");
    }
    
    if(ps2x.ButtonPressed(PSB_PAD_RIGHT))  //x refers to the array which will be in terms of 000x 0000 if switch corresponding to up is pressed and up refers to enum
    {
        //    rightPressed(); 
            Serial.println("right");
    }   

    if(ps2x.ButtonPressed(PSB_PAD_LEFT))  //x refers to the array which will be in terms of 000x 0000 if switch corresponding to up is pressed and up refers to enum
    {
           //leftPressed(); 
           Serial.println("left");
    }
    
     if(ps2x.ButtonPressed(PSB_PAD_DOWN)) //x refers to the array which will be in terms of 000x 0000 if switch corresponding to up is pressed and up refers to enum
    {
          //downPressed();
          Serial.println("down");
    }
    
     if(ps2x.ButtonPressed(PSB_SELECT))
     {  
          //selPressed();
          Serial.println("select");
    }
    
    if(ps2x.ButtonPressed(PSB_START))
    {  
          //  startPressed();
            Serial.println("start");
     }
    
    if(ps2x.ButtonPressed(PSB_TRIANGLE))
    {   
         //  trianglePressed();
            Serial.println('T');     
    }  
    
    if(ps2x.ButtonPressed(PSB_CIRCLE))
     {
         //   circlePressed();
            Serial.println('C'); 
     }
     
     if(ps2x.ButtonPressed(PSB_CROSS))
     {
       Serial.println("Xc");

     }
     
     if(ps2x.ButtonPressed(PSB_SQUARE))
     {
        //  squarePressed();
           Serial.println('S');     
     }

     
 delay(wirelessdelay);  
}

void scalePS2value(){
      ySquare_leftdistance=(basePS2_Y-data.Ly)/basePS2_Y;
      xSquare_leftdistance=(data.Lx-128)/128.0;
      ySquare_rightdistance=(basePS2_Y-data.Ry)/basePS2_Y;
      xSquare_rightdistance=(data.Rx-128)/128.0;
      if(xSquare_leftdistance==0 && ySquare_leftdistance==0){
      xCircle_leftdistance=0;
      yCircle_leftdistance=0; 
      }
      else{
      xCircle_leftdistance= xSquare_leftdistance *sqrt(pow(xSquare_leftdistance,2)+pow(ySquare_leftdistance,2)-(pow(xSquare_leftdistance,2)*pow(ySquare_leftdistance,2)))/sqrt(pow(xSquare_leftdistance,2)+pow(ySquare_leftdistance,2));
      yCircle_leftdistance= ySquare_leftdistance *sqrt(pow(xSquare_leftdistance,2)+pow(ySquare_leftdistance,2)-(pow(xSquare_leftdistance,2)*pow(ySquare_leftdistance,2)))/sqrt(pow(xSquare_leftdistance,2)+pow(ySquare_leftdistance,2));
      }
      if(xSquare_rightdistance==0 && ySquare_rightdistance==0){
      xCircle_rightdistance=0;
      yCircle_rightdistance=0; 
      }
      else{
      xCircle_rightdistance= xSquare_rightdistance *sqrt(pow(xSquare_rightdistance,2)+pow(ySquare_rightdistance,2)-(pow(xSquare_rightdistance,2)*pow(ySquare_rightdistance,2)))/sqrt(pow(xSquare_rightdistance,2)+pow(ySquare_rightdistance,2));
      yCircle_rightdistance= ySquare_rightdistance *sqrt(pow(xSquare_rightdistance,2)+pow(ySquare_rightdistance,2)-(pow(xSquare_rightdistance,2)*pow(ySquare_rightdistance,2)))/sqrt(pow(xSquare_rightdistance,2)+pow(ySquare_rightdistance,2));
      }
      
      LeftAnalogDistance=sqrt((xCircle_leftdistance)*(xCircle_leftdistance)+(yCircle_leftdistance)*(yCircle_leftdistance));
      LeftAnalogTheta=atan2(yCircle_leftdistance,xCircle_leftdistance)*(180.0/3.14);
      LeftAnalogTheta=(int(LeftAnalogTheta)+360)%360;
      RightAnalogDistance=sqrt((xCircle_rightdistance)*(xCircle_rightdistance)+(yCircle_rightdistance)*(yCircle_rightdistance));
      RightAnalogTheta=atan2(yCircle_rightdistance,xCircle_rightdistance)*(180.0/3.14);
      RightAnalogTheta=(int(RightAnalogTheta)+360)%360;
      
} 



