#include <Arduino.h>

class HourLeds {
  public:
    void set(uint8_t hour);
    void clear();
    void ring(uint16_t speed, uint8_t loops=1);
};


class MinuteLeds {  
  public:
    void set(uint8_t minute);
    void clear();
    void pomodoroSet(uint8_t minute);
    void ring(uint16_t speed, uint8_t loops=1);
};
