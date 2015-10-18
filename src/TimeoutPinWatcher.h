#ifndef PinWatcher_h
#define PinWatcher_h

typedef void (*timeout_pin_watcher_callback)(void);

class TimeoutPinWatcher {
public:
  static const int DIGITAL = 1;
  static const int ANALOG = 2;
public:
  TimeoutPinWatcher();
  void attach(int pin, timeout_pin_watcher_callback callback, int type = DIGITAL);
  void attachDigital(int pin, timeout_pin_watcher_callback callback);
  void attachAnalog(int pin, timeout_pin_watcher_callback callback);
  uint32_t setTimeout(uint32_t timeout);
  void run();
private:
  int _pin;
  int _type;
  timeout_pin_watcher_callback _callback;
  int _lastValue;
  int _currentValue;
  uint32_t _timeout;
  unsigned long _lasttime;
};

#endif
