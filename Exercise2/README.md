# Exercise2

<img alt="image" src="https://raw.githubusercontent.com/Maksasj/VuRoboticsExercises/refs/heads/main/photo.png" />

### Problem

Implemented concurrent, non-blocking task execution on Arduino Uno.

### Design

The Arduino Uno code implements concurrent task management for several processes: blinking LEDs, detecting button presses, and updating a TFT display.

There are four LED lights: blue, red, yellow, and green.

**LED Control (Scheduled Tasks)**

The blue, red, and yellow LEDs are controlled by a scheduled task system utilizing hardware timers and interrupts. This approach provides non-blocking execution.

* Blue LED: Blinks every $\mathbf{1}$ second.
* Red LED: Blinks every $\mathbf{0.5}$ seconds.
* Yellow LED: Blinks every $\mathbf{0.25}$ seconds.

**Button-Controlled LED (External Interrupts)**

The green LED is managed by an external interrupt triggered by a button press. When the button is pressed, the interrupt service routine (ISR) executes non-blockingly (it doesn't pause the main loop). This ISR handles switch debouncing and then toggles the green LED's state.

**Display Management (Main Loop)**

The main program loop is dedicated to TFT display updates. Because the TFT library itself uses a timer for its operations, and since display operations are time-consuming, this dedicated main loop allows for the display logic to be run in a non-blocking, cooperative manner, avoiding the need to pause the time-critical LED and button tasks.

After executing a specific task, the resulting data is stored in its respective variable. These variables are then backed up to EEPROM memory every 100 milliseconds as a scheduled task.

### EEPROM layout

1. Label: SAVES_ADDRESS, Address: 0. Used to store number of saves
1. Label: BLUE_LICHTS_ADDRESS, Address: 2. Used to store number of blue light flashes
1. Label: RED_LICHTS_ADDRESS, Address: 4. Used to store number of red light flashes
1. Label: YELLOW_LICHTS_ADDRESS, Address: 6. Used to store number of yellow light flashes
1. Label: GREEN_LICHTS_ADDRESS, Address: 8. Used to store number of green light flashes
1. Label: FRAMES_LICHTS_ADDRESS, Address: 10. Used to store number of display update frames

### Building steps

1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Download ino file and open it in IDE
3. Select your connected Arduino UNO
4. Build and upload sketch to arduino.

### ISR roles

1. ISR(TIMER1_COMPA_vect) Used to run scheduled timer tasks. This interrupt is triggered by timer every 1 millisecond.
2. void ISR_button_pressed(void). Used to update green light. This interrupt is triggered by attached button.

### Timer configuration
Timer is configured to run every 1 millisecond.

### Future improvements

Future work can improve different aspects of the circuit. 

One of the most possible improvements is utilizing an external power supply to power other things such as servos. The current TFT display takes a lot of power to run. The circuit fails to run a servo at the same time, as I have tested. 

The next possible improvement is the creation of a queue-based automatic scheduling system with lambdas, where a centralized queue with task callbacks can be used for easier task management.

A third crucial improvement is to refine the button debouncing implementation on the input switch. While the current debouncing mechanism is functional, it doesn't fully eliminate the issue, indicating a need for a more robust solution.