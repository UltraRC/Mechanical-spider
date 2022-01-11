# Robot Hexapod - By Reuben van Dorp
This project is an 18-DOF hexapod robot based around an ESP32 micocontroller board. The electrical and mechanical construction was completed quickely, however the software for the robot has taken a while longer to finish due to the complexity of controlling 6 legs together.

## Features
- A robot hexapod, each leg contains 3 servo motors
- The robot uses two 16 channel pca9865 pwm controllers connected to an arduino nano to control all 18 servos all at once
- A 6-channel RC receiver and Spektrum DX6 radio acts as a means to wirelessly control the robot
![Robot Spider](/images/spiderNEW.jpg)
