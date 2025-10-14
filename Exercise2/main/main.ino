#include <TFT.h>  
#include <SPI.h>
#include <EEPROM.h>

#define TFT_CHIP_SELECT_PIN   10
#define TFT_DATA_CONTROL_PIN   9
#define TFT_RESET_PIN  8

#define BLUE_DIODE_PIN 6
#define RED_DIODE_PIN 3
#define YELLOW_DIODE_PIN 4
#define GREEN_DIODE_PIN 5
#define BUTTON_PIN 2

TFT TFTscreen = TFT(TFT_CHIP_SELECT_PIN, TFT_DATA_CONTROL_PIN, TFT_RESET_PIN);

// task timers
volatile int tasks_timers[5];

#define SAVES_ADDRESS 0
#define BLUE_LICHTS_ADDRESS 2
#define RED_LICHTS_ADDRESS 4
#define YELLOW_LICHTS_ADDRESS 6
#define GREEN_LICHTS_ADDRESS 8
#define FRAMES_LICHTS_ADDRESS 10

volatile int saves;
volatile int blue_lights;
volatile int red_lights;
volatile int yellow_lights;
volatile int green_lights;
volatile int frames;

volatile int button_bounce_delay = 300;
volatile int button_bounce_time = 0;

void setup() {
  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextSize(2);
  TFTscreen.setTextColor(0, 0);
  
  pinMode(BLUE_DIODE_PIN, OUTPUT);
  pinMode(RED_DIODE_PIN, OUTPUT);
  pinMode(YELLOW_DIODE_PIN, OUTPUT);
  pinMode(GREEN_DIODE_PIN , OUTPUT);

  pinMode(BUTTON_PIN , INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), ISR_button_pressed, RISING);

  /*
  EEPROM.put(SAVES_ADDRESS, 0);
  EEPROM.put(BLUE_LICHTS_ADDRESS, 0);
  EEPROM.put(RED_LICHTS_ADDRESS, 0);
  EEPROM.put(YELLOW_LICHTS_ADDRESS, 0);
  EEPROM.put(GREEN_LICHTS_ADDRESS, 0);
  EEPROM.put(FRAMES_LICHTS_ADDRESS, 0);
  */

  EEPROM.get(SAVES_ADDRESS, saves);
  EEPROM.get(BLUE_LICHTS_ADDRESS, blue_lights);
  EEPROM.get(RED_LICHTS_ADDRESS, red_lights);
  EEPROM.get(YELLOW_LICHTS_ADDRESS, yellow_lights);
  EEPROM.get(GREEN_LICHTS_ADDRESS, green_lights);
  EEPROM.get(FRAMES_LICHTS_ADDRESS, frames);

  setupTimer1();

  // reset task timers
  for(int i = 0; i < 5; ++i)
    tasks_timers[i] = 0;

  button_bounce_time = millis();
}

void loop() {
  TFTscreen.background(0, 0, 0);
  char data[80];

  {
    TFTscreen.stroke(255, 255, 255);
    sprintf(data, "s: %d", saves);
    TFTscreen.text(data, 6, 8);
  }

  {
    TFTscreen.stroke(0, 0, 255);
    sprintf(data, "b: %d", blue_lights);
    TFTscreen.text(data, 6, 24);
  }

  {
    TFTscreen.stroke(255, 0, 0);
    sprintf(data, "r: %d", red_lights);
    TFTscreen.text(data, 6, 40);
  }

  {
    TFTscreen.stroke(255, 255, 0);
    sprintf(data, "y: %d", yellow_lights);
    TFTscreen.text(data, 6, 56);
  }

  {
    TFTscreen.stroke(0, 255, 0);
    sprintf(data, "g: %d", green_lights);
    TFTscreen.text(data, 6, 72);
  }

  {
    TFTscreen.stroke(0, 255, 255);
    sprintf(data, "f: %d", frames);
    TFTscreen.text(data, 6, 88);
  }

  ++frames;
  delay(200);
}

void ISR_button_pressed(void) {
  if((millis() - button_bounce_time) > button_bounce_delay) {
    ++green_lights;
    digitalWrite(5,  !digitalRead(5));
    button_bounce_time = millis();
  }
}

void setupTimer1() {
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  TCCR1B |= (1 << WGM12);

  OCR1A = 1999;

  TCCR1B |= (1 << CS11);

  TIMSK1 |= (1 << OCIE1A);
}

ISR(TIMER1_COMPA_vect) {
  for(int i = 0; i < 5; ++i)
    ++tasks_timers[i];
  
  // perfom task 1
  if(tasks_timers[0] >= 1000) {
    ++yellow_lights;
    digitalWrite(YELLOW_DIODE_PIN, !digitalRead(YELLOW_DIODE_PIN));
    tasks_timers[0] = 0;
  }

  // perfom task 2
  if(tasks_timers[1] >= 500) {
    ++red_lights;
    digitalWrite(RED_DIODE_PIN, !digitalRead(RED_DIODE_PIN));
    tasks_timers[1] = 0;
  }

  // perfom task 3
  if(tasks_timers[2] >= 250) {
    ++blue_lights;
    digitalWrite(BLUE_DIODE_PIN, !digitalRead(BLUE_DIODE_PIN));
    tasks_timers[2] = 0;
  }

  // perfom task 4
  if(tasks_timers[3] >= 100) {
    ++saves;

    if(saves > 32766) saves = 0;
    if(blue_lights > 32766) blue_lights = 0;
    if(yellow_lights > 32766) yellow_lights = 0;
    if(green_lights > 32766) green_lights = 0;
    if(frames > 32766) frames = 0;

    EEPROM.put(SAVES_ADDRESS, saves);
    EEPROM.put(BLUE_LICHTS_ADDRESS, blue_lights);
    EEPROM.put(RED_LICHTS_ADDRESS, red_lights);
    EEPROM.put(YELLOW_LICHTS_ADDRESS, yellow_lights);
    EEPROM.put(GREEN_LICHTS_ADDRESS, green_lights);
    EEPROM.put(FRAMES_LICHTS_ADDRESS, frames);

    tasks_timers[3] = 0; 
  }
}
