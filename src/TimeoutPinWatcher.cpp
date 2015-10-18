#include <Arduino.h>
#include "TimeoutPinWatcher.h"

TimeoutPinWatcher::TimeoutPinWatcher() {
  _lastValue = -1;
  _currentValue = -1;
}

void TimeoutPinWatcher::attach(int pin, timeout_pin_watcher_callback callback, int type) {
  _pin = pin;
  _callback = callback;
  _type = type;
  _timeout = 1000;
  _lasttime = 0;
}

void TimeoutPinWatcher::attachDigital(int pin, timeout_pin_watcher_callback callback) {
  attach(pin, callback, DIGITAL);
}

void TimeoutPinWatcher::attachAnalog(int pin, timeout_pin_watcher_callback callback) {
  attach(pin, callback, ANALOG);
}

uint32_t TimeoutPinWatcher::setTimeout(uint32_t timeout) {
  return _timeout = timeout;
}

void TimeoutPinWatcher::run() {
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
