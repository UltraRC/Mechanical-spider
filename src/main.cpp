#include <Arduino.h>
#include<math.h>
#include "SetServos.h"
#include "ReceiverInput.h"
#include "InverseKinematics.h"

void setStorage();

/*
- There are 6 channels comming into the receiver
- Channels 0-->5 proceed. THR:0, AIL:1, ELE:2, RUD:3, GEA:4, AUX:5
- Values will be from 500 --> 2500 uS centered on 1500 uS as the neutral position
*/

void setup()
{
  Serial.begin(9600);
  servoInitialize();
}

void loop()
{
  /*
  int time = 5;
  int min = -100;
  int max = -30;

  for(int y=max;y>min;y--){
    int x = 30;
    updateAngles(x,y);
    for(int leg=1;leg<=6;leg++){
      setAngle(leg,2,getTheta1());
      setAngle(leg,3,getTheta2());
    }
    delay(time);
    servoUpdate();
  }

  for(int y=min;y<max;y++){
    int x = 30;
    updateAngles(x,y);
    for(int leg=1;leg<=6;leg++){
      setAngle(leg,2,getTheta1());
      setAngle(leg,3,getTheta2());
    }
    delay(time);
    servoUpdate();
  }
  */

 setStorage();
 servoUpdate();
}

void setStorage(){
  setAngle(1,1,60);
  setAngle(2,1,0);
  setAngle(3,1,-60);
  setAngle(4,1,60);
  setAngle(5,1,0);
  setAngle(6,1,-60);
  for(int leg=1;leg<=6;leg++){
    setAngle(leg,2,90);
    setAngle(leg,3,-115);
  }
}