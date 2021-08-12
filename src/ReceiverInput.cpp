#include <Arduino.h>
#include "ReceiverInput.h"

int receiverInputs[6]; // uS receiver input values stored as an int
int lastPulseTime = 0;
volatile int valuesFromReceiver[6]; // yeet

/**
Constructor:
- boolean degrees, true for return in degrees [-90,90] or false for uS [500,2500]
- Initilize all input pins
- Set default values for valuesFromReceiver[] array
- Enable interupts for each of the RC input pins and associate each pin with a function
*/

/**
 * Constructor: Configures receiver GPIO pins as interrupt input pins
 */
ReceiverInput::ReceiverInput()
{
  pinMode(RC_THR_PIN, INPUT_PULLDOWN);
  pinMode(RC_AIL_PIN, INPUT_PULLDOWN);
  pinMode(RC_ELE_PIN, INPUT_PULLDOWN);
  pinMode(RC_RUD_PIN, INPUT_PULLDOWN);
  pinMode(RC_GEA_PIN, INPUT_PULLDOWN);
  pinMode(RC_AUX_PIN, INPUT_PULLDOWN);

  for (int i = 0; i <= 5; i++)
  { // Set the default values for the array which holds receiver values
    valuesFromReceiver[i] = 1500;
  }

  attachInterrupt(RC_THR_PIN, thrInterrupt, CHANGE);
  attachInterrupt(RC_AIL_PIN, ailInterrupt, CHANGE);
  attachInterrupt(RC_ELE_PIN, eleInterrupt, CHANGE);
  attachInterrupt(RC_RUD_PIN, rudInterrupt, CHANGE);
  attachInterrupt(RC_GEA_PIN, geaInterrupt, CHANGE);
  attachInterrupt(RC_AUX_PIN, auxInterrupt, CHANGE);
}

void ReceiverInput::updateReceiverValues()
{
  noInterrupts();
  memcpy(receiverInputs, (const void *)valuesFromReceiver, sizeof(valuesFromReceiver));
  interrupts();
}

/**
 * Prints the pulse widths of all 6 channels
 */
void ReceiverInput::printReceiverValues()
{
  for (int i = 0; i <= 5; i++)
  {
    Serial.print(receiverInputs[i]);
    Serial.print("\t");
  }
  Serial.print("\n");
}

/**
 * THR:0, AIL:1, ELE:2, RUD:3, GEA:4, AUX:5 
 **/
int ReceiverInput::getChannel(int channel)
{
  if (channel > 5 || channel < 0)
  { // Outside the scope of channel
    return 0;
  }
  return pulseWidthToDegrees(receiverInputs[channel]);
}

/**
 * Maps pulse width from [500,2500] uS to [-90,90] degrees
 * @param pulseWidth 
 * @return Type long receiver input +-90 degrees
 */
double ReceiverInput::pulseWidthToDegrees(int pulseWidth)
{
  return map(pulseWidth, 500, 2500, -90, 90);
}

void readReceiverInput(uint8_t pin, uint8_t channel)
{
  if (digitalRead(pin) == HIGH) lastPulseTime = micros();
  else
  {
    uint16_t pulseLength = (uint16_t)(micros() - lastPulseTime);
    valuesFromReceiver[channel] = pulseLength;
  }
}

void IRAM_ATTR thrInterrupt() { readReceiverInput(RC_THR_PIN, 0); }
void IRAM_ATTR ailInterrupt() { readReceiverInput(RC_AIL_PIN, 1); }
void IRAM_ATTR eleInterrupt() { readReceiverInput(RC_ELE_PIN, 2); }
void IRAM_ATTR rudInterrupt() { readReceiverInput(RC_RUD_PIN, 3); }
void IRAM_ATTR geaInterrupt() { readReceiverInput(RC_GEA_PIN, 4); }
void IRAM_ATTR auxInterrupt() { readReceiverInput(RC_AUX_PIN, 5); }