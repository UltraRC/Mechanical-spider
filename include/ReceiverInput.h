#ifndef RECEIVER_INPUT_H
#define RECEIVER_INPUT_H

/*
- There are 6 channels comming into the receiver: THR, AIL, ELE, RUD, GEA, AUX
- They are referenced via type Channel_t (an enum)
- Pulsewidth values will be from 500 --> 2500 uS centered on 1500 uS as the neutral position
- Returned channels will be in the range [MIN_NORM_INPUT, MAX_NORM_INPUT] which is [1000, 1000] by default
*/

// Physical pin connections from receiver to the micro-controller
// Define here the I/O pins on your micro-controller which correspond to a
// particular channel
#define THR_PIN 36
#define AIL_PIN 39
#define ELE_PIN 34
#define RUD_PIN 35
#define GEA_PIN 32
#define AUX_PIN 33

#define NUM_CHANNELS 6

#define MIN_PULSEWIDTH 500 // uS
#define MAX_PULSEWIDTH 2500

#define MIN_NORM_INPUT -1000 // Range of channel signal
#define MAX_NORM_INPUT 1000

typedef enum {
    THR = 0,
    AIL,
    ELE,
    RUD,
    GEA,
    AUX
} Channel_t;

/**
 * - Call update() to update the channels array
 * - Call getChannel(Channel_t channel) to get a particular channel
 * - Call getChannelPulsewidth(Channel_t channel) to get a particular channel pulse width in uS
 * - Channels are an ENUM with entries: THR, AIL, ELE, RUD, GEA, AUX
 */
class ReceiverInput
{
public:
    ReceiverInput();
    void update();
    int32_t getChannel(Channel_t channel);
    uint32_t getChannelPulsewidth(Channel_t channel);

private:
    void copyBuffer();
    int32_t pulsewidthNormalize(Channel_t channel);
    void initPulsewidthArray();
};

void measurePulseWidth(uint8_t pin, Channel_t channel, uint32_t* pulseStart);
void IRAM_ATTR thrInterrupt();
void IRAM_ATTR ailInterrupt();
void IRAM_ATTR eleInterrupt();
void IRAM_ATTR rudInterrupt();
void IRAM_ATTR geaInterrupt();
void IRAM_ATTR auxInterrupt();
#endif //RECEIVERINPUT_H