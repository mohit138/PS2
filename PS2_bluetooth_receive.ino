#include <PS2X_lib.h>
#include <EasyTransfer.h>
#include <SPI.h>

#define SerialPS2 Serial2
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



void setup() {
  Serial.begin(9600);
  BluetoothSerial.begin(38400);
  ET.begin(details(data),&BluetoothSerial);
}

void loop() {
  if(ET.receiveData())
  {
   // Serial.println(data.ps2data);
    ps2x.buttons=data.ps2data;
  }
  scalePS2value();
  PS2executePressed();
}



void PS2executePressed(){    
    if (ps2x.ButtonPressed(PSB_PAD_UP))  //x refers to the array which will be in terms of 000x 0000 if switch corresponding to up is pressed and up refers to enum
    { 
         // upPressed();
          Serial.println('s');
    }
    
    if(ps2x.ButtonReleased(PSB_PAD_UP))
    {
    //   upReleased();
     Serial.println("UR");
    }
    
    if(ps2x.ButtonPressed(PSB_PAD_RIGHT))  //x refers to the array which will be in terms of 000x 0000 if switch corresponding to up is pressed and up refers to enum
    {
        //    rightPressed(); 
            Serial.println('r');
    }
     
    if(ps2x.ButtonReleased(PSB_PAD_RIGHT))
    {
          Serial.println("RR");
         // rightReleased();
    }
        
    if(ps2x.ButtonPressed(PSB_PAD_LEFT))  //x refers to the array which will be in terms of 000x 0000 if switch corresponding to up is pressed and up refers to enum
    {
           //leftPressed(); 
           Serial.println('l');
    }
    
    if(ps2x.ButtonReleased(PSB_PAD_LEFT))
    {
         Serial.println("LR");         
        // leftReleased();
    }
    
     if(ps2x.ButtonPressed(PSB_PAD_DOWN)) //x refers to the array which will be in terms of 000x 0000 if switch corresponding to up is pressed and up refers to enum
    {
          //downPressed();
          Serial.println('D');
    }
     
     if(ps2x.ButtonReleased(PSB_PAD_DOWN)) //x refers to the array which will be in terms of 000x 0000 if switch corresponding to up is pressed and up refers to enum
     {
         Serial.println("DR");
     
        //downReleased();
     }
    
     if(ps2x.ButtonPressed(PSB_SELECT))
     {  
          //selPressed();
          Serial.println('E');
    }
    if(ps2x.ButtonReleased(PSB_SELECT))
    {
         // selReleased();
         Serial.println("ER");     
    }
    
    if(ps2x.ButtonPressed(PSB_START))
    {  
          //  startPressed();
            Serial.println('S');
     }
    
    if(ps2x.ButtonReleased(PSB_START)) 
    {
       Serial.println("SR");    
       // startReleased();
    }
    
    if(ps2x.ButtonPressed(PSB_TRIANGLE))
    {   
         //  trianglePressed();
            Serial.println('T');     
    }  
    
    if(ps2x.ButtonReleased(PSB_TRIANGLE))
    {
       Serial.println("TR");     
       // triangleReleased();
    }
    
    if(ps2x.ButtonPressed(PSB_CIRCLE))
     {
         //   circlePressed();
            Serial.println('C'); 
     }
     
     if(ps2x.ButtonReleased(PSB_CIRCLE))
     {
       Serial.println("CR");
       //circleReleased();
     }
   
     
     if(ps2x.ButtonReleased(PSB_CROSS))
     {
       Serial.println("XR");
//        flag=0;
      //  crossReleased();
      }
     
        
    
     if(ps2x.ButtonPressed(PSB_SQUARE))
     {
        //  squarePressed();
           Serial.println('S');     
     }

     if(ps2x.ButtonReleased(PSB_SQUARE))
     {
       Serial.println("SR");
     //squareReleased();
     }  
  
      if(ps2x.ButtonPressed(PSB_R1))
     {
       //   r1Pressed();    
          Serial.println("r1");
     }

      if(ps2x.ButtonReleased(PSB_R1))
     {
         Serial.println("HR");
         //r1Released();
     }
    
      if(ps2x.ButtonPressed(PSB_R2))
     {
          //r2Pressed();
          Serial.println("r2");
     }

      if(ps2x.ButtonReleased(PSB_R2))
     {
       Serial.println("IR");
        //r2Released();
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



