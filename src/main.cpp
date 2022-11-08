#include <Arduino.h>
#include "thread.h"

#define RED_PIN 3
#define BLUE_PIN 5
#define GREEN_PIN 6

#define STEPS 2
#define DELAY_LENGTH 40 / (3 * 2)

static T_COROUTINE(red) {
  static int red = 0xFF;

  T_START()
  for(;red > 0; red-=STEPS)
  {
    analogWrite(RED_PIN, red);
    delay(DELAY_LENGTH);
  }
  T_YIELD()
  for(;red < 0xFF; red+=STEPS)
  {
    analogWrite(RED_PIN, red);
    delay(DELAY_LENGTH);
  }
  T_END()
}

static T_COROUTINE(blue)
{
  static int blue = 0;

  T_START()
  for(;blue < 0xFF; blue+=STEPS)
  {
    analogWrite(BLUE_PIN, blue);
    delay(DELAY_LENGTH);
  }

  T_YIELD()
  for(;blue > 0; blue-=STEPS)
  {
    analogWrite(BLUE_PIN, blue);
    delay(DELAY_LENGTH);
  }
  T_END()
}

static T_COROUTINE(green)
{
  static int green = 0;

  T_START()
  for(;green < 0xFF; green+=STEPS)
  {
    analogWrite(GREEN_PIN, green);
    delay(DELAY_LENGTH);
  }
  T_YIELD()
  for(;green > 0; green-=STEPS)
  {
    analogWrite(GREEN_PIN, green);
    delay(DELAY_LENGTH);
  }
  T_END()
}

void setup() {
  T_INIT(red);
  T_INIT(blue);
  T_INIT(green);

  Serial.begin(9600);
}

struct thread_info threads[] = {
  T_INFO(green), T_INFO(red),
  T_INFO(blue), T_INFO(green),
  T_INFO(red), T_INFO(blue),
};
const size_t thread_count = ARRAY_LEN(threads);

static size_t cur_thread = 0;
void loop() {
  T_CALL(threads[cur_thread++ % thread_count]);
}
