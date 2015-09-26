#ifndef PinWatcher_h
#define PinWatcher_h

typedef void (*pin_watcher_callback)(void);

class PinWatcher {
public:
  PinWatcher();
  void attach(int pin, pin_watcher_callback callback, int type = DIGITAL);
  void attachDigital(int pin, pin_watcher_callback callback);
  void attachAnalog(int pin, pin_watcher_callback callback);
  void run();
  static const int DIGITAL = 1;
  static const int ANALOG = 2;
private:
  int _pin;
  int _type;
  pin_watcher_callback _callback;
  int _lastValue;
  int _currentValue;
};

#endif
