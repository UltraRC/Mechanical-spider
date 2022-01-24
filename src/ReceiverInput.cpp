#include <Arduino.h>
#include "ReceiverInput.h"

uint32_t receiverPulsewidth[NUM_CHANNELS]; // Holds pulsewidths (500,2500) uS for each channel
volatile uint32_t receiverPulsewidthBuffer[NUM_CHANNELS];

ReceiverInput::ReceiverInput()
{
  pinMode(THR_PIN, INPUT);
  pinMode(AIL_PIN, INPUT);
  pinMode(ELE_PIN, INPUT);
  pinMode(RUD_PIN, INPUT);
  pinMode(GEA_PIN, INPUT);
  pinMode(AUX_PIN, INPUT);
  
  initPulsewidthArray();

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

/**
 * @brief Returns channel value between -1000 and 1000 centered on 0
 */
int32_t ReceiverInput::getChannel(Channel_t channel)
{
  return pulsewidthNormalize(channel);
}

uint32_t ReceiverInput::getChannelPulsewidth(Channel_t channel)
{
  return receiverPulsewidth[channel];
}

void ReceiverInput::copyBuffer()
{
  noInterrupts();
  memcpy(receiverPulsewidth, (const void *)receiverPulsewidthBuffer, sizeof(receiverPulsewidthBuffer));
  interrupts();
}

int32_t ReceiverInput::pulsewidthNormalize(Channel_t channel)
{
  int32_t pw = getChannelPulsewidth(channel); // pw ==> Pulsewidth
  pw = map(pw, MIN_PULSEWIDTH, MAX_PULSEWIDTH, MIN_NORM_INPUT, MAX_NORM_INPUT);
  return constrain(pw, MIN_NORM_INPUT, MAX_NORM_INPUT);
}

void ReceiverInput::initPulsewidthArray()
{
  for(uint8_t i=THR; i<=AUX; i++) {
    receiverPulsewidthBuffer[i] = (MAX_PULSEWIDTH + MIN_PULSEWIDTH) / 2;
  }
}

void measurePulseWidth(uint8_t pin, Channel_t channel, uint32_t* pulseStart)
{
  if(digitalRead(pin)) {
    *pulseStart = micros();
  } else {
    receiverPulsewidthBuffer[channel] = micros() - *pulseStart;
  }
}

// ----------------------- Interrupt functions ------------------------

void IRAM_ATTR thrInterrupt()
{
  static uint32_t pulseStart = 0;
  measurePulseWidth(THR_PIN, THR, &pulseStart);
}

void IRAM_ATTR ailInterrupt()
{
  static uint32_t pulseStart = 0;
  measurePulseWidth(AIL_PIN, AIL, &pulseStart);
}

void IRAM_ATTR eleInterrupt()
{
  static uint32_t pulseStart = 0;
  measurePulseWidth(ELE_PIN, ELE, &pulseStart);
}

void IRAM_ATTR rudInterrupt()
{
  static uint32_t pulseStart = 0;
  measurePulseWidth(RUD_PIN, RUD, &pulseStart);
}

void IRAM_ATTR geaInterrupt(){
  static uint32_t pulseStart = 0;
  measurePulseWidth(GEA_PIN, GEA, &pulseStart);
}

void IRAM_ATTR auxInterrupt()
{
  static uint32_t pulseStart = 0;
  measurePulseWidth(AUX_PIN, AUX, &pulseStart);
}