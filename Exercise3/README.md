# Exercise2

<img alt="image" src="https://raw.githubusercontent.com/Maksasj/VuRoboticsExercises/refs/heads/main/Exercise3/photo.jpg" />

### Problem

Make use of shift register.

### Design

The Arduino Uno code implements concurrent task management for several processes: blinking LEDs (using shift register), and updating a TFT display.

There are 8 LED lights: 8x blue.

**LED Control (Scheduled Tasks)**

Blue LEDs are controlled by a shift register, each LED is fired only once one after another, after all LEDs are on shift register is reseted. Process repeats indefinitly.

**Display Management (Main Loop)**

The main program loop is dedicated to display updates. Because the TFT library itself uses a timer for its operations, and since display operations are time-consuming, this dedicated main loop allows for the display logic to be run in a non-blocking, cooperative manner, avoiding the need to pause the time-critical LED and button tasks.

### Building steps

1. Install [Arduino IDE](https://www.arduino.cc/en/software)
1.1 Install library U8g2
2. Download ino file and open it in IDE
3. Select your connected Arduino UNO
4. Build and upload sketch to arduino.

### Parts
1. Quantity: 1, Part  Arduino Uno R3
1. Quantity: 8, Part Blue LED
1. Quantity: 8, Part 220 Ω Resistor
1. Quantity: 1, Part Oled SSD1306 Display White

### ISR roles

1. ISR(TIMER1_COMPA_vect) Used to run scheduled timer tasks. This interrupt is triggered by timer every 1 millisecond.

### Timer configuration
Timer is configured to run every 1 millisecond.

### Future improvements

Future work can improve different aspects of the circuit. 

Possible improvement is the creation of a queue-based automatic scheduling system with lambdas, where a centralized queue with task callbacks can be used for easier task management.

For shift register could be implemented more precise event driven system with sceduling different pin values.

