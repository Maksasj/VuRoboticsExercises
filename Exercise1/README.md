## Smart ventilation system

<img alt="image" src="https://raw.githubusercontent.com/Maksasj/VuRoboticsExercise1/refs/heads/main/photo.png" />

### Problem
Hot Lithuanian summers are a problem a lot of people can relate to, as sudden temperature changes hit homes, apartments, and even factories, production lines. This project tends to address this problem by designing smart and economic ventilation system.

### Design
Photoresistor detects change of brightness signalling to the intensity of the sun light. Based on this information microcontroller controls fan spinning direction. Effectively night time pumping cold air into the building and day time pumping hot air outside of the building. Simple potentiometer could be used to controll speed.

### Part list

Full CSV file could be found [here](https://github.com/Maksasj/VuRoboticsExercise1/blob/main/parts.csv) 

1. Name: U2, Quantity: 1, Part: Arduino Uno R3
1. Name: U1, Quantity: 1, Part: H-bridge Motor Driver
1. Name: M1, Quantity: 1, Part: DC Motor
1. Name: Rpot3, Quantity: 1, Part: 250 kΩ Potentiometer
1. Name: P1, Quantity: 1,3Part: 0 , 5  Power Supply
1. Name: R1, Quantity: 1, Part: Photoresistor
1. Name: R2, Quantity: 1,4Part: .7 kΩ Resistor


### Schematics and Demonstration
- Device schematics could be found [here](https://github.com/Maksasj/VuRoboticsExercise1/blob/main/schematic.pdf)
- Device workin demonstration could be seen [here](https://github.com/Maksasj/VuRoboticsExercise1/blob/main/demonstration.mkv)

### Future improvements
Future system could be improved with adding more user feedback such as display and operational lights.

As well as adding more sensor for more fine tuned temperature control (Fan speed can be controlled with temperature sensor)

Other sensors could be used to ensure all windows or doors are closed for most efficient cooling strategy.

Scheduling system.



