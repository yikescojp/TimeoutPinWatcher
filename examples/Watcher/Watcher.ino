#include <TimeoutPinWatcher.h>

#define SENSOR_PIN 2
#define LED_PIN 13

TimeoutPinWatcher watcher;

void onChangeSensorPin() {
  digitalWrite(LED_PIN, digitalRead(SENSOR_PIN));
  delay(50);
}

void setup() {
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  watcher.attach(SENSOR_PIN, onChangeSensorPin);
  watcher.setTimeout(2000);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  watcher.run();
}
