#include <TFT.h>  
#include <SPI.h>
#include <EEPROM.h>

const int LED_PIN_1S = LED_BUILTIN;
volatile unsigned long interrupt_count_1s = 0;
 
// const int LED_PIN_2S = 12;
// volatile unsigned int timer2_2s_counter = 0;
// const int TICKS_PER_2_SECONDS = 2000;

// --- Timer 3 (3.0 seconds) Configuration (Software-counted) ---
// const int LED_PIN_3S = 11; // Pin 11 LED toggles every 3 seconds
// This counter tracks 1ms ticks for the 3.0-second task.
// volatile unsigned int timer3_3s_counter = 0;
// const int TICKS_PER_3_SECONDS = 3000;

#define TFT_CHIP_SELECT_PIN   10
#define TFT_DATA_CONTROL_PIN   9
#define TFT_RESET_PIN  8

TFT TFTscreen = TFT(TFT_CHIP_SELECT_PIN, TFT_DATA_CONTROL_PIN, TFT_RESET_PIN);

void setup() {
  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextSize(2);

  pinMode(6, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5 , OUTPUT);

  pinMode(2 , INPUT_PULLUP );
  attachInterrupt(digitalPinToInterrupt(2), ISR_button_pressed, RISING );

  setupTimer1();
  // setupTimer2();
}

void loop() {
  int value;
  EEPROM.get(0, value);

  TFTscreen.stroke(255, 255, 255);

  char data[80];
  sprintf(data, "number %d", value);
  ++value;

  TFTscreen.background(0, 0, 0);
  TFTscreen.text(data, 6, 57);

  EEPROM.write(0, value);

  // int buttonState = digitalRead(6);
  // digitalWrite(5, buttonState);


  // digitalWrite(2, HIGH);  // turn the LED on (HIGH is the voltage level)
  // delay(1000);                      // wait for a second
  //digitalWrite(2, LOW);   // turn the LED off by making the voltage LOW
  // delay(1000);                      // wait for a second
}

void ISR_button_pressed(void) {
  digitalWrite(5,  !digitalRead(5));
  attachInterrupt(digitalPinToInterrupt(2), ISR_button_pressed, RISING );
}

void setupTimer1() {
  // Stop Timer1, clear registers, reset counter
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  // CTC Mode (WGM12 set)
  TCCR1B |= (1 << WGM12);

  // Set Compare Match Register for 15624 counts (1 second)
  OCR1A = 15624;

  // Set prescaler to 1024 and start timer (CS12 and CS10 set)
  TCCR1B |= (1 << CS12) | (1 << CS10);

  // Enable Timer1 compare match interrupt (OCIE1A)
  TIMSK1 |= (1 << OCIE1A);
}

ISR(TIMER1_COMPA_vect) {
  digitalWrite(6, !digitalRead(6));
  digitalWrite(3, !digitalRead(3));
  digitalWrite(4, !digitalRead(4));
  // digitalWrite(5, !digitalRead(5));
  // digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
                   // wait for a second
  // digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  // delay(1000);                      // wait for a second
}

void setupTimer2() {
  // Stop Timer2, clear registers, reset counter
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;

  // CTC Mode (WGM21 set in TCCR2A)
  TCCR2A |= (1 << WGM21);

  // Set Compare Match Register for 249 counts (1 millisecond)
  OCR2A = 249;

  // Set prescaler to 64 and start timer (CS22 set in TCCR2B)
  TCCR2B |= (1 << CS22);

  // Enable Timer2 compare match interrupt (OCIE2A)
  TIMSK2 |= (1 << OCIE2A);
}

/**
 * @brief ISR for Timer2 Compare Match A (1 millisecond interval).
 * This ISR serves as the ticker for all millisecond-based tasks (2s and 3s).
 * IMPORTANT: Keep all logic inside this ISR extremely lean and fast.
 */
ISR(TIMER2_COMPA_vect) {
  /*
  // --- 2.0 Second Task Logic ---
  timer2_2s_counter++;
  if (timer2_2s_counter >= TICKS_PER_2_SECONDS) {
    // Execute the 2-second task: toggle the Pin 12 LED
    digitalWrite(LED_PIN_2S, !digitalRead(LED_PIN_2S));
    // Reset the counter
    timer2_2s_counter = 0;
  }

  // --- 3.0 Second Task Logic ---
  timer3_3s_counter++;
  if (timer3_3s_counter >= TICKS_PER_3_SECONDS) {
    // Execute the 3-second task: toggle the Pin 11 LED
    digitalWrite(LED_PIN_3S, !digitalRead(LED_PIN_3S));
    // Reset the counter
    timer3_3s_counter = 0;
  }
  */
}
