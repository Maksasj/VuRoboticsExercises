#include <SPI.h>
#include <EEPROM.h>
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define REGISTER_LATCH_PIN 5  // Latch pin of 74HC595 is connected to Digital pin 5
#define REGISTER_CLOCK_PIN 6  // Clock pin of 74HC595 is connected to Digital pin 6
#define REGISTER_DATA_PIN 4   // Data pin of 74HC595 is connected to Digital pin 4

// task timers
volatile int tasks_timers[5];
volatile int shift_count;
volatile int resets_count;
volatile byte leds_value;
volatile int bit_shift;
volatile int ball_position;
volatile int ball_direction;

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void prepare_draw(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void draw_scene() {
  u8g2.drawStr(10, 5, "Reset count:");
  u8g2.setCursor(85, 5);
  u8g2.print(resets_count);
  
  u8g2.drawStr(10, 20, "Shift count:");
  u8g2.setCursor(85, 20);
  u8g2.print(shift_count);

  u8g2.drawCircle(ball_position, 50, 5);

  ball_position += ball_direction;

  if(ball_position < 8 || ball_position > 120)
    ball_direction = -ball_direction;

  u8g2.drawFrame(0, 0, u8g2.getDisplayWidth(), u8g2.getDisplayHeight());
}

void setup() {
  // Setup timer task sysytem
  setupTimer1();

  for(int i = 0; i < 5; ++i)
    tasks_timers[i] = 0;

  // Setup shift register
  pinMode(REGISTER_LATCH_PIN, OUTPUT);
  pinMode(REGISTER_DATA_PIN, OUTPUT);
  pinMode(REGISTER_CLOCK_PIN, OUTPUT);

  // Setup variables
  shift_count = 0;
  resets_count = 0;
  leds_value = 0;
  bit_shift = 0;
  ball_position = 50;
  ball_direction = -1;

  // Setup display  
  u8g2.begin();
}

void loop() {
  u8g2.firstPage(); 

  do {
    prepare_draw();
    draw_scene();
  } while(u8g2.nextPage());

  delay(50);
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
  if(tasks_timers[0] >= 100) {
    bitSet(leds_value, bit_shift);

    digitalWrite(REGISTER_LATCH_PIN, LOW);
    shiftOut(REGISTER_DATA_PIN, REGISTER_CLOCK_PIN, LSBFIRST, leds_value);
    digitalWrite(REGISTER_LATCH_PIN, HIGH);
    ++bit_shift;
    ++shift_count;

    if(bit_shift >= 8) {
      bit_shift = 0;
      leds_value = 0;
      ++resets_count;
    }

    tasks_timers[0] = 0;
  }
}