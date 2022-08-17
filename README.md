# RWD-Car-Module

This project is a simulation of an RWD car module based on an Arduino Uno controller board in the Tinkercad circuits simulator. 
Things that can be controlled are driving direct or reverse, speed, steering, objects' distance from the car back for the 
ultrasonic sensor to signal close objects using a buzzer, and outer light for the photoresistor to adjust front lighting.

## Hardware

Components connected to Arduino:

- DC Motors: two rear wheels
- H-bridge, for DC Motors
- Servo motors, for front wheels steering
- LCD 16x2, shows speed and shift
- Potentiometers, for controlling speed and steering (representing joystick module)
- Ultrasonic sensor
- Piezo buzzer, connected with the ultrasonic sensor

Components not connected to Arduino:

- Two Bulbs
- Photoresistor and relay to control bulb's brightness

The realistic connecting scheme while the simulation is on is shown below: (for electrical scheme see 
[documentation](https://docs.google.com/viewer?url=https://github.com/Yaly0/RWD-Car-Module/files/9331047/dok.pdf) p. 7 and 8).

<img width="517" alt="sim on uss" src="https://user-images.githubusercontent.com/95139567/184473965-b504d6d6-7a6a-4c23-a6aa-9ee3d55ee45f.png">

## Software

The code is written in C++ for Arduino, details of how the code works are explained in the 
[documentation](https://docs.google.com/viewer?url=https://github.com/Yaly0/RWD-Car-Module/files/9331047/dok.pdf), other than primary commands
in the code, Ackermann's steering geometry and its' consequences were implemented.

---
For more information and all other details see the 
[documentation](https://docs.google.com/viewer?url=https://github.com/Yaly0/RWD-Car-Module/files/9331047/dok.pdf) (written in Bosnian language).

Click [here](https://www.tinkercad.com/things/gQCxgLPuAym) for testing the project on the official Tinkercad webpage.

(Simulate -> Start Simulation -> adjustable components: potentiometers, ultrasonic sensor and photoresistor)
