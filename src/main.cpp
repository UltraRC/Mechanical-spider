#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <math.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40); // Default i2C address
//uint8_t servoNum = 0;                                        // Servo counter from 0-15 (16 in total), an unsigned 8-bit integer
double frequency = 0.5; // Hz
float time; // Stores the time in seconds since the program started

#define SERVOMIN 205;  // This is the 'minimum' pulse length count (out of 4096) ==> 45 degrees
#define SERVOMAX 410;  // This is the 'maximum' pulse length count (out of 4096) ==> 135 degrees
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

void setup()
{
  Serial.begin(9600);
  pwm.begin();
  pwm.setOscillatorFrequency(27E6);
  pwm.setPWMFreq(SERVO_FREQ);
  pwm.setPWM(15, 0, 2048);
}

void loop()
{
  time = millis() * 0.001; // Time in seconds

  for(int servoNum=0;servoNum<=15;servoNum++){
    double servMax = (1.0/20)*4096.0;
    double servMin = (2.0/20)*4096.0;
    double amplitude = 0.5 * (servMax - servMin);
    double shift = 0.5 * (servMax - servMin) + SERVOMIN;
    double phaseShift = 1 * PI * (servoNum / 15.0);

    //double onTime = amplitude * sin(2*PI*frequency*time - phaseShift) + shift;
    double onTime = (1.5/20.0) * 4096.0; // 1.0 ms is 45 degrees, 1.5 ms is 90 degrees, 2.0 ms is 135 degrees
    pwm.setPWM(servoNum, 0, onTime); // All servos
    //pwm.setPWM(2, 0, onTime);

  }
  
}