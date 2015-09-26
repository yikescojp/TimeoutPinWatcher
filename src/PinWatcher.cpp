#include <Arduino.h>
#include "PinWatcher.h"

PinWatcher::PinWatcher() {
  _lastValue = -1;
  _currentValue = -1;
}

void PinWatcher::attach(int pin, pin_watcher_callback callback, int type) {
  _pin = pin;
  _callback = callback;
  _type = type;
}

void PinWatcher::attachDigital(int pin, pin_watcher_callback callback) {
  attach(pin, callback, DIGITAL);
}

void PinWatcher::attachAnalog(int pin, pin_watcher_callback callback) {
  attach(pin, callback, ANALOG);
}

void PinWatcher::run() {
  switch (_type) {
    case DIGITAL:
      _currentValue = digitalRead(_pin);
      break;
    case ANALOG:
      _currentValue = analogRead(_pin);
      break;
    default:
      _currentValue = -1;
      break;
  }
  if (_currentValue != _lastValue) {
    (*_callback)();
  }
  _lastValue = _currentValue;
}
