#define PHOTO_IN A1
#define SPEED_IN A0

#define MOTOR_CONTROL_1 2
#define MOTOR_CONTROL_2 3
#define MOTOR_SPEED_OUT 5

#define LIGHT_DETECTION_CYCLE 20
#define MOTOR_DIRECTION_THRESHOLD 512

// Environment data, measurements 
struct Environment {
	int lightLevel;
	int motorSpeed;
	// ...
};

Environment currentEnvironment;

void setup()
{
	currentEnvironment = Environment {};
	
	pinMode(MOTOR_CONTROL_1, OUTPUT);
	pinMode(MOTOR_CONTROL_2, OUTPUT);
	pinMode(MOTOR_SPEED_OUT, OUTPUT);
}

void measureLight() 
{
	currentEnvironment.lightLevel = 0;

	// Ensure light change is consistent across multiple time stamps
	for(int i = 0; i < LIGHT_DETECTION_CYCLE; ++i) {
		currentEnvironment.lightLevel += analogRead(PHOTO_IN);
		delay(10);
	}

	currentEnvironment.lightLevel /= LIGHT_DETECTION_CYCLE;
}

void controlMotorDirection()
{
	if(currentEnvironment.lightLevel < MOTOR_DIRECTION_THRESHOLD) {
		// CCW direction
		digitalWrite(MOTOR_CONTROL_1, LOW);
		digitalWrite(MOTOR_CONTROL_2, HIGH);
	} else {
		// CW direction
		digitalWrite(MOTOR_CONTROL_1, HIGH);
		digitalWrite(MOTOR_CONTROL_2, LOW);
	}
}

void loop()
{
	measureLight();

	controlMotorDirection();

	// Measure motor speed
	currentEnvironment.motorSpeed = analogRead(SPEED_IN) / 4;
	analogWrite(MOTOR_SPEED_OUT, currentEnvironment.motorSpeed);
}
