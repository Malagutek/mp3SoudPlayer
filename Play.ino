/******************************************************************************
PlayATrack.ino
Cytron EasyMP3 Shield Library example sketch
Created by Ng Beng Chet @ Cytron Technologies Sdn Bhd 
Original Creation Date: Mar 10, 2016
https://github.com/CytronTechnologies/Cytron-EasyMP3-Shield

Modified from DFPlayer_Mini_Mp3 Library examples
Credit to lisper <lisper.li@dfrobot.com> @ DFRobot
Original Creation Date: May 30, 2014
https://github.com/DFRobot/DFPlayer-Mini-mp3

!!! Description Here !!!

Development environment specifics:
	IDE: Arduino 1.6.7
	Hardware Platform: Arduino Uno or any other compatible boards
	Cytron EasyMP3 Shield Version: 1.0

Distributed as-is; no warranty is given.
******************************************************************************/
#include <CytronEZMP3.h>


CytronEZMP3 mp3;

void setup () {
	Serial.begin(9600);
  if(!mp3.begin(2, 3))
  {
    Serial.println("Init failed");
    while(1);
  }
  mp3.setVolume(25);
  Serial.print("Device: ");
  Serial.println(mp3.getCurrentDevice()==1?"U-Disk":"microSD");

  Serial.print("Total files: ");
  Serial.println(mp3.getTotalFiles());
  KeyboardInit();
  LedPinsInit();
}

void KeyboardInit()
{
  pinMode(A0, INPUT_PULLUP);  
  pinMode(A1, INPUT_PULLUP);  
  pinMode(5, INPUT_PULLUP);  
  pinMode(A3, INPUT_PULLUP);  
  pinMode(A4, INPUT_PULLUP);  
  pinMode(A5, INPUT_PULLUP);  
}

int KeyboardCheck()
{
   
  if (!digitalRead(A0)) return 1;
  if (!digitalRead(A1)) return 2;
  if (!digitalRead(5))  return 3;
  if (!digitalRead(A3)) return 4;
  if (!digitalRead(A4)) return 5;
  if (!digitalRead(A5)) return 6;
  return 100; 
}


void LedPinsInit()
{
    
  pinMode(6, OUTPUT);  // 1.mp3
  pinMode(7, OUTPUT);  // 2.mp3
  pinMode(8, OUTPUT);  // 3.mp3
  pinMode(9, OUTPUT);  // 4.mp3
  pinMode(10, OUTPUT); // 5.mp3
  pinMode(11, OUTPUT); // 6.mp3

}

void LedOnOff(int ledn,bool state)
{
    int led_n=ledn+5;
    digitalWrite(led_n,state);
}

uint8_t kbds;
uint8_t mp3Status;
int nr_k=100; 
void loop () {
   
   //uint8_t mp3Status;
   
   mp3.playPhysical(KeyboardCheck());
   LedOnOff(KeyboardCheck(),HIGH);
   kbds=KeyboardCheck();
   Serial.println("Now plg track " + (String)mp3.getTrackNo());
   Serial.println("Cur Status: " + (String)mp3.getCurrentStatus ());
   Serial.println("kbd: " +  (String)KeyboardCheck());
   bool znal = LOW;
   Serial.print("Znal: " + znal);
   Serial.println(znal);
  
//   Serial.println(znal);
   while(mp3.getCurrentStatus ()!=0 && !znal)
    {
     mp3Status = mp3.getCurrentStatus();
     Serial.println("Current Status: " + (String)mp3.getCurrentStatus()); 
     Serial.println("Now playing track " + (String)mp3.getTrackNo());
     Serial.println("kbdd: " +  (String)KeyboardCheck());
     if (KeyboardCheck!=100) znal=HIGH;
     delay(1000);
    }   
    if (kbds==100)
    { 
      for (int il=1;il<7;il++)
       LedOnOff(il,LOW);
    }
    kbds=100;
}
