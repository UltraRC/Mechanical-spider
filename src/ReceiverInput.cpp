#include <Arduino.h>
#include <EnableInterrupt.h>
#include "ReceiverInput.h"

int receiverInputs[6]; // uS receiver input values stored as an int
int lastPulseTime = 0;
volatile int valuesFromReceiver[6];
int lastTime = 0;

/*
Constructor:
- Initilize all input pins
- Set default values for valuesFromReceiver[] array
- Enable interupts for each of the RC input pins and associate each pin with a function
*/
ReceiverInput::ReceiverInput(){
    
    for(int i=7;i<=12;i++){ // Initilize all input pins
        pinMode(i, INPUT);
    }

    for(int i=0;i<=5;i++){ // Set the default values for the array which holds receiver values
        valuesFromReceiver[i]=1500;
    }
    enableInterrupt(RC_THR_PIN, thrInterrupt, CHANGE);
    enableInterrupt(RC_AIL_PIN, ailInterrupt, CHANGE);
    enableInterrupt(RC_ELE_PIN, eleInterrupt, CHANGE);
    enableInterrupt(RC_RUD_PIN, rudInterrupt, CHANGE);
    enableInterrupt(RC_GEA_PIN, geaInterrupt, CHANGE);
    enableInterrupt(RC_AUX_PIN, auxInterrupt, CHANGE);
}

void ReceiverInput::readReceiverInput(int pin, int channel){
  if(digitalRead(pin) == HIGH){
    lastPulseTime = micros();
  }else{
    uint16_t pulseLength =  (uint16_t) (micros() - lastPulseTime);
    valuesFromReceiver[channel] = pulseLength;
  }
}

void ReceiverInput::updateReceiverValues(){
    noInterrupts();
    memcpy(receiverInputs, (const void *)valuesFromReceiver, sizeof(valuesFromReceiver));
    interrupts();
}

void ReceiverInput::printReceiverValues(){
    Serial.print("THR: ");Serial.print(receiverInputs[0]);Serial.print("\t");
    Serial.print("AIL: ");Serial.print(receiverInputs[1]);Serial.print("\t");
    Serial.print("ELE: ");Serial.print(receiverInputs[2]);Serial.print("\t");
    Serial.print("RUD: ");Serial.print(receiverInputs[3]);Serial.print("\t");
    Serial.print("GEA: ");Serial.print(receiverInputs[4]);Serial.print("\t");
    Serial.print("AUX: ");Serial.print(receiverInputs[5]);Serial.print("\t");
    Serial.println();
}

int ReceiverInput::getChannel(int channel){
  if(channel > 5 || channel < 0){  // Outside the scope of channel
    return 1500;
  }
  return receiverInputs[channel];
}

void ReceiverInput::thrInterrupt(){readReceiverInput(RC_THR_PIN, 0);}
void ReceiverInput::ailInterrupt(){readReceiverInput(RC_AIL_PIN, 1);}
void ReceiverInput::eleInterrupt(){readReceiverInput(RC_ELE_PIN, 2);}
void ReceiverInput::rudInterrupt(){readReceiverInput(RC_RUD_PIN, 3);}
void ReceiverInput::geaInterrupt(){readReceiverInput(RC_GEA_PIN, 4);}
void ReceiverInput::auxInterrupt(){readReceiverInput(RC_AUX_PIN, 5);}