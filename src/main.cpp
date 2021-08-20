#include <Arduino.h>
#include "ReceiverInput.h"

ReceiverInput receiver;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    receiver.update();

    for(uint8_t i=THR; i<=AUX; i++) {
        printf("%d\t", receiver.getChannelPulsewidth((Channel_t)i));
    }
    printf("\n");
}