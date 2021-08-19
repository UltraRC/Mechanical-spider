#ifndef RECEIVER_INPUT_H
#define RECEIVER_INPUT_H

/*
- There are 6 channels comming into the receiver
- Channels 0-->5 proceed. THR:0, AIL:1, ELE:2, RUD:3, GEA:4, AUX:5
- Values will be from 500 --> 2500 uS centered on 1500 uS as the neutral position
*/

// Physical pin connections from receiver to the micro-controller
#define THR_PIN 36
#define AIL_PIN 39
#define ELE_PIN 34
#define RUD_PIN 35
#define GEA_PIN 32
#define AUX_PIN 33

#define NUM_CHANNELS 6

#define MIN_PULSEWIDTH 1500 // uS
#define MAX_PULSEWIDTH 2500

#define MIN_NORM_INPUT -100
#define MAX_NORM_INPUT 100

typedef enum {
    THR = 0,
    AIL,
    ELE,
    RUD,
    GEA,
    AUX
} Channel_t;

uint32_t receiverPulsewidth[NUM_CHANNELS]; // Holds pulsewidths (500,2500) uS for each channel
volatile uint32_t receiverPulsewidthBuffer[NUM_CHANNELS];

class ReceiverInput
{
public:
    ReceiverInput();
    void update();
    double getChannel(Channel_t channel);
    uint32_t getChannelPulsewidth(Channel_t channel);

private:
    void copyBuffer();
    double pulsewidthNormalize(Channel_t channel);
};

void measurePulseWidth(uint8_t pin, Channel_t channel);
void IRAM_ATTR thrInterrupt();
void IRAM_ATTR ailInterrupt();
void IRAM_ATTR eleInterrupt();
void IRAM_ATTR rudInterrupt();
void IRAM_ATTR geaInterrupt();
void IRAM_ATTR auxInterrupt();
#endif