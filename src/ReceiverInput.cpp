#include <Arduino.h>
#include "ReceiverInput.h"

ReceiverInput::ReceiverInput()
{
  pinMode(THR_PIN, INPUT_PULLDOWN);
  pinMode(AIL_PIN, INPUT_PULLDOWN);
  pinMode(ELE_PIN, INPUT_PULLDOWN);
  pinMode(RUD_PIN, INPUT_PULLDOWN);
  pinMode(GEA_PIN, INPUT_PULLDOWN);
  pinMode(AUX_PIN, INPUT_PULLDOWN);
  
  attachInterrupt(THR_PIN, thrInterrupt, CHANGE);
  attachInterrupt(AIL_PIN, ailInterrupt, CHANGE);
  attachInterrupt(ELE_PIN, eleInterrupt, CHANGE);
  attachInterrupt(RUD_PIN, rudInterrupt, CHANGE);
  attachInterrupt(GEA_PIN, geaInterrupt, CHANGE);
  attachInterrupt(AUX_PIN, auxInterrupt, CHANGE);
}

void ReceiverInput::update()
{
  copyBuffer();
}

double ReceiverInput::getChannel(Channel_t channel)
{
  return pulsewidthNormalize(channel);
}

uint32_t ReceiverInput::getChannelPulsewidth(Channel_t channel)
{
  return receiverPulsewidth[channel];
}

double ReceiverInput::pulsewidthNormalize(Channel_t channel)
{
  uint32_t pw = getChannelPulsewidth(channel); // pw ==> Pulsewidth
  pw = map(pw, MIN_PULSEWIDTH, MAX_PULSEWIDTH, MIN_NORM_INPUT, MAX_NORM_INPUT);
  return constrain(pw, MIN_NORM_INPUT, MAX_NORM_INPUT);

}

void ReceiverInput::copyBuffer()
{
  noInterrupts();
  memcpy(receiverPulsewidth, (const void *)receiverPulsewidthBuffer, sizeof(receiverPulsewidthBuffer));
  interrupts();
}

void measurePulseWidth(uint8_t pin, Channel_t channel)
{
  static uint32_t pulseStart = 0;
  if(digitalRead(pin)) {
    pulseStart = micros();
  } else {
    receiverPulsewidthBuffer[channel] = micros() - pulseStart;
  }
}

void IRAM_ATTR thrInterrupt() { measurePulseWidth(THR_PIN, THR); }
void IRAM_ATTR ailInterrupt() { measurePulseWidth(AIL_PIN, AIL); }
void IRAM_ATTR eleInterrupt() { measurePulseWidth(ELE_PIN, ELE); }
void IRAM_ATTR rudInterrupt() { measurePulseWidth(RUD_PIN, RUD); }
void IRAM_ATTR geaInterrupt() { measurePulseWidth(GEA_PIN, GEA); }
void IRAM_ATTR auxInterrupt() { measurePulseWidth(AUX_PIN, AUX); }