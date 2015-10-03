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
  _timeout = 1000;
  _lasttime = 0;
}

void PinWatcher::attachDigital(int pin, pin_watcher_callback callback) {
  attach(pin, callback, DIGITAL);
}

void PinWatcher::attachAnalog(int pin, pin_watcher_callback callback) {
  attach(pin, callback, ANALOG);
}

uint32_t PinWatcher::setTimeout(uint32_t timeout) {
  return _timeout = timeout;
}

void PinWatcher::run() {
  if (millis() - _lasttime < _timeout) return;
  _lasttime = millis();
  
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
