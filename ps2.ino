#include <SPI.h>
   
int Confidencelevel[5];
enum {x,l1,l2,r1,r2};
int L1counter=0,L2counter=0;
int xflag=0,l1flag=0,l2flag=0,r1flag=0,r2flag=0;
int xhold=0,l1hold=0,l2hold=0,r1hold=0,r2hold=0;
/*void scalePS2value(){
      ySquare_leftdistance=(basePS2_Y-ps2x.Analog(PSS_LY))/basePS2_Y;
      xSquare_leftdistance=(-ps2x.Analog(PSS_LX)+128)/128.0;
      ySquare_rightdistance=(basePS2_Y-ps2x.Analog(PSS_RY))/basePS2_Y;
      xSquare_rightdistance=(-ps2x.Analog(PSS_RX)+128)/128.0;
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
      RightAnalogDistance=sqrt((xCircle_rightdistance)*(xCircle_rightdistance)+(yCircle_rightdistance)*(yCircle_rightdistance));
      RightAnalogTheta=atan2(yCircle_rightdistance,xCircle_rightdistance)*(180.0/3.14);
} 

*/
void initPS2()
{
   error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);
  if(error == 0)
    Serial.print("Found Controller, configured successful ");
  else if(error == 1)
    Serial.println("No controller found"); 
  
  type = ps2x.readType(); 
  
  switch(type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2: 
      Serial.print("GuitarHero Controller found ");
      break;
    case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
  }
}





void getPS2value()
{ 
  ps2x.read_gamepad(false,vibrate);          //read controller  
}

void rightPressed(){  
  SerialPS2.write('r');
}  
void rightReleased(){
}
void leftPressed(){
  SerialPS2.write('l');
  //SerialPS2.print('l');
} 
void leftReleased(){
  
}
void upPressed(){
  frontpressed = 1;
}
void upReleased(){
  frontpressed=0;  
}
void downPressed(){
  backpressed=1;
} 
void downReleased(){
  backpressed=0;
}
void selPressed(){
}
void selReleased(){
}
void startPressed(){
}
void startReleased(){  
}
void trianglePressed(){
    SerialPS2.write('s');
    
}
void triangleReleased(){
}
void circleReleased(){
}
 void circlePressed(){
}
void crossPressed(){
    Serial.println('x');
}
void crossReleased(){
}
void squarePressed(){
}  
void squareReleased(){
}

void l1Pressed(){
Serial.println("l1");
}
void l1Released(){  
}  
void r1Released(){
}
void r1Pressed(){
}  
void l2Released(){
}
void l2Pressed(){
Serial.println("l2");
}
void r2Released(){
}
void r2Pressed(){
  SerialPS2.write('w');
}
void L1L2pressed(){
Serial.println("l1l2c");
}
                
void PS2executePressed(){

    if(ps2x.ButtonReleased(PSB_L1))
     {
       l1hold=0;
     
     }   
     
     if(ps2x.ButtonPressed(PSB_L1))
     {
       l1hold=1;
      }
     
     
     if(ps2x.ButtonPressed(PSB_L2))
     {    
          l2hold=1;
    }

    if(ps2x.ButtonReleased(PSB_L2))
    {
        l2hold=0;
        
    }   
    if(ps2x.Button(PSB_L1) && l1hold==1){
      L1counter++;
        if(L1counter>10){
          if(ps2x.Button(PSB_L2) && l2hold==1 && l1hold==1){
            L2counter++;
              if(L2counter>10){
                L1L2pressed();
                l1hold=0;
                L1counter=0;
                L2counter=0;
                l2hold=0;
              }  
          }
          if(L1counter > 10/*900000*/ && L2counter==0 && l1hold==1 && l2hold==0){
            l1Pressed();
            L1counter=0;
            L2counter=0;
            l1hold=0;
            l2hold=0;
          }
        }
    }
       
    if(ps2x.Button(PSB_L2) && l2hold==1){
      L2counter++;
        if(L2counter>10){
          if(ps2x.Button(PSB_L1) && l1hold==1 && l2hold==1){
            L1counter++;
              if(L1counter>10){
                L1L2pressed();
                l1hold=0;
                L1counter=0;
                L2counter=0;
                l2hold=0;
              }  
          }
          if(L2counter > 10 && L1counter==0 && l2hold==1 && l1hold==0){
            l2Pressed();
            L1counter=0;
            L2counter=0;
            l1hold=0;
            l2hold=0;
          }
        }
    }
    if (ps2x.ButtonPressed(PSB_PAD_UP))  //x refers to the array which will be in terms of 000x 0000 if switch corresponding to up is pressed and up refers to enum
    { 
          upPressed();
          Serial.println('s');
    }
    if(ps2x.ButtonReleased(PSB_PAD_UP))
    {
       upReleased();
 //     Serial.println("UR");
    }
    
    if(ps2x.ButtonPressed(PSB_PAD_RIGHT))  //x refers to the array which will be in terms of 000x 0000 if switch corresponding to up is pressed and up refers to enum
     {
            rightPressed(); 
            Serial.println('r');
     }
     
    if(ps2x.ButtonReleased(PSB_PAD_RIGHT))
     {
          Serial.println("RR");
          rightReleased();
     }
        
    if(ps2x.ButtonPressed(PSB_PAD_LEFT))  //x refers to the array which will be in terms of 000x 0000 if switch corresponding to up is pressed and up refers to enum
     {
           leftPressed(); 
           Serial.println('l');
     }
    if(ps2x.ButtonReleased(PSB_PAD_LEFT))
     {
         Serial.println("LR");         
         leftReleased();
     }
    
     if(ps2x.ButtonPressed(PSB_PAD_DOWN)) //x refers to the array which will be in terms of 000x 0000 if switch corresponding to up is pressed and up refers to enum
     {
          downPressed();
          Serial.println('D');
     }
     
     if(ps2x.ButtonReleased(PSB_PAD_DOWN)) //x refers to the array which will be in terms of 000x 0000 if switch corresponding to up is pressed and up refers to enum
     {
         Serial.println("DR");
     
        downReleased();
     }
    
     if(ps2x.ButtonPressed(PSB_SELECT))
     {  
          selPressed();
          Serial.println('E');
    }
    if(ps2x.ButtonReleased(PSB_SELECT))
    {
          selReleased();
         Serial.println("ER");     
    }
    
    if(ps2x.ButtonPressed(PSB_START))
    {  
            startPressed();
            Serial.println('S');
     }
    
    if(ps2x.ButtonReleased(PSB_START)) 
    {
       Serial.println("SR");    
        startReleased();
    }
    
    if(ps2x.ButtonPressed(PSB_TRIANGLE))
    {   
           trianglePressed();
            Serial.println('T');     
    }  
    
    if(ps2x.ButtonReleased(PSB_TRIANGLE))
    {
       Serial.println("TR");     
        triangleReleased();
    }
    
    if(ps2x.ButtonPressed(PSB_CIRCLE))
     {
            circlePressed();
            Serial.println('C'); 
     }
     
     if(ps2x.ButtonReleased(PSB_CIRCLE))
     {
       Serial.println("CR");
       circleReleased();
     }
   
     
     if(ps2x.ButtonReleased(PSB_CROSS))
     {
       Serial.println("XR");
//        flag=0;
        crossReleased();
      }
     
        
    
     if(ps2x.ButtonPressed(PSB_SQUARE))
     {
          squarePressed();
           Serial.println('S');     
     }

     if(ps2x.ButtonReleased(PSB_SQUARE))
     {
       Serial.println("SR");
     squareReleased();
     }  
  
   
     
 
   if(ps2x.ButtonPressed(PSB_R1))
    {
          r1Pressed();    
          Serial.println("r1");
    }

    if(ps2x.ButtonReleased(PSB_R1))
    {
         Serial.println("HR");
         r1Released();
    }
    if(ps2x.ButtonPressed(PSB_R2))
    {
          r2Pressed();
          Serial.println("r2");
    }

    if(ps2x.ButtonReleased(PSB_R2))
    {
       Serial.println("IR");
        r2Released();
    }
 delay(wirelessdelay);  
}


