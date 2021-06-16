#ifndef RECEIVER_INPUT_H
#define RECEIVER_INPUT_H

/*
- There are 6 channels comming into the receiver
- Channels 0-->5 proceed. THR:0, AIL:1, ELE:2, RUD:3, GEA:4, AUX:5
- Values will be from 500 --> 2500 uS centered on 1500 uS as the neutral position
*/

#define RC_THR_PIN 36
#define RC_AIL_PIN 39
#define RC_ELE_PIN 34
#define RC_RUD_PIN 35
#define RC_GEA_PIN 32
#define RC_AUX_PIN 33

class ReceiverInput
{
public:
    // Constructor
    ReceiverInput(boolean degrees);

    // Methods
    void updateReceiverValues();
    void printReceiverValues();

    int getChannel(int channel);

private:
    double pulseWidthToDegrees(int pulseWidth);
};

void readReceiverInput(uint8_t pin, uint8_t channel);
void IRAM_ATTR thrInterrupt();
void IRAM_ATTR ailInterrupt();
void IRAM_ATTR eleInterrupt();
void IRAM_ATTR rudInterrupt();
void IRAM_ATTR geaInterrupt();
void IRAM_ATTR auxInterrupt();
#endif