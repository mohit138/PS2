
#include <PS2X_lib.h>
PS2X ps2x;
#include <EasyTransfer.h>
#include <SPI.h>
//#define SerialPS2 Serial
#define BluetoothSerial Serial
int error=0;
byte type = 0;
byte vibrate = 0;



EasyTransfer ET;


struct PS2_data{
 int32_t ps2data;
 uint8_t Rx;
 uint8_t Ry;
 uint8_t Lx;
 uint8_t Ly;
 
};
PS2_data data;

void initPS2()
{
  
     error = ps2x.config_gamepad(13,11,10,12, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
      // dat_ 12   cmd __ 11    sel ___ 10     clk____ 13 
 if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
   Serial.println("holding L1 or R1 will print out the analog stick values.");
   Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
 
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   //Serial.print(ps2x.Analog(1), HEX);
   
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
       break;
     }
    
    
}

void getPS2value()
{ 
  ps2x.read_gamepad(false,vibrate);
  data.ps2data=ps2x.buttons_2;
  data.Rx=ps2x.PS2data[5];
  data.Ry=ps2x.PS2data[6];
  data.Lx=ps2x.PS2data[7];
  data.Ly=ps2x.PS2data[8]; 
}

void setup() {
  Serial.begin(9600);
  BluetoothSerial.begin(38400);
  initPS2();
  ET.begin(details(data),&BluetoothSerial);
}

void loop() {
  getPS2value();
  //Serial.println(data.ps2data);
  ET.sendData();
  delay(50); 
}
