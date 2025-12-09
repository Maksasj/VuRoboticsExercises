# Exercise4

<img alt="image" src="https://raw.githubusercontent.com/Maksasj/VuRoboticsExercises/refs/heads/main/Exercise4/photo.jpg" />

### Problem
Create a simple tamagotchi-like robot. Robot should support multiple states and transitions. React to environment changes and events. Be a cute to have on your desk :).

### Design
All I2C supporting sensors and devices are connected to a single i2c bus which is connected to esp microcontroller 5 and 6 pin. Touch sensor is connected to a 0 pin. Robot have emotion state as well as behavior. State transitions happens on different events: mood threshold, environment event, timeout event.   

### Building steps
1. Install [Visual Studio Code](https://code.visualstudio.com/)
1.1 Install ESP-IDF Extension
1.2 Install ESP-IDF v5.1.6 or above (code have been tested with 5.1.6 and 5.2.6)
1.3 Install all additional tool required for EPS-IDF
2. Clone repository locally and open in IDE
3. Select correct version of ESP-IDF
4. Select correct esp version COM port and programmer
5. Press Build, Flash, Monitor button.
6. Enjoy 

### Part list
Full CSV file could be found [here](https://github.com/Maksasj/VuRoboticsExercises/blob/main/Exercise4/parts.csv) 

1. ESP32-C3 Mini 1x
1. MPU6050 sensor 1x
1. BMP280 sensor 1x
1. TTP223 sensor 1x
1. TP4056 Li-Pol Battery Charge Protection Board
1. Li-Pol battery 3.7v

### Schematics and Demonstration
- Device schematics could be found [here](https://github.com/Maksasj/VuRoboticsExercises/blob/main/Exercise4/schematic.png)
- Device working demonstration could be seen [here](https://github.com/Maksasj/VuRoboticsExercises/blob/main/Exercise4/demonstration.mp4)

### Future improvements
- v1.1 Version
    - Fully soldering battery module to the robot. 
- v2.0 Version
    - Implementing more complex behavior engine and more environments events.
    - Adding simple speaker for more output deviced.
    - Rechargable battery charge level as mood affecting criteria.
    - More interactions.