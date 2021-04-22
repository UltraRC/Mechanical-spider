#ifndef RECEIVER_INPUT_H
#define RECEIVER_INPUT_H

#define RC_THR_PIN 7
#define RC_AIL_PIN 8
#define RC_ELE_PIN 9
#define RC_RUD_PIN 10
#define RC_GEA_PIN 11
#define RC_AUX_PIN 12

/*
- There are 6 channels comming into the receiver
- Channels 0-->5 proceed. THR:0, AIL:1, ELE:2, RUD:3, GEA:4, AUX:5
- Values will be from 500 --> 2500 uS centered on 1500 uS as the neutral position
*/

class ReceiverInput {
    public:
    // Constructor
    ReceiverInput();

    // Methods
    void updateReceiverValues();
    void printReceiverValues();

    int getChannel(int channel);

    private:
    void static readReceiverInput(int pin, int channel);
    void static thrInterrupt();
    void static ailInterrupt();
    void static eleInterrupt();
    void static rudInterrupt();
    void static geaInterrupt();
    void static auxInterrupt();
};
#endif