/*
 * The effects of sleep mode in this case:
 * Battery capacity of a 2032 is +-240mAh.
 * Current consumption when active is 13.6mA en in sleep mode is 260µA.
 * So in sleep mode the watch will last 38.5 days.
 * Without sleep it would last 17.5 hours.
 */

#include <avr/sleep.h>
#include "Led_Classes.h"

#define BUTTON PIN_PB1  // Pin for the button

#define TIME_UNTIL_SLEEP 8

HourLeds hourleds;  // Objects with methods to control the LED arrays
MinuteLeds minuteleds;

uint8_t hours = 0;  // Variables to store the watch time
uint8_t minutes = 0;
uint8_t seconds = 0;

uint8_t pomodoroMinutes = 25;  // Variables to store the pomodoro time
uint8_t pomodoroSeconds = 0;
uint8_t pomodoroCount = 0;

uint8_t activeWatchSeconds = 0;  // Variable to store the ammount of seconds the program is in watch mode to enter standby mode
volatile bool wakeUp = true;

/*
 * MainStates:
 *  adjust -> In this state you can adjust the watch time to the correct time
 *  watch -> In this state the watch will display the current time
 *  pomodoroTimer -> In this state the watch will go into pomodoro timer mode
 *  sleep -> The program will enter this state when going into standby mode
 *           In this state the program will do nothing but the RTC will keep working
 */

enum MainStates {
  adjust, watch, pomodoroTimer, sleep
};

MainStates state = adjust;

/*
 * AdjustStates:
 *  adjustHour -> In this state you will be able to adjust the hour the watch will display by using the button
 *  adjustMinute -> In this state you will be able to adjust the minutes the watch will display by using the button
 */

enum AdjustStates {
  adjustHour, adjustMinute
};

AdjustStates adjustState = adjustHour;

/*
 * PomodoroStates:
 *  pomodoro -> In this state the watch will count to 15 minutes (= 1 pomodoro)
 *  shortBreak -> In this state (after the 15 minutes) the watch will count to 5 minutes
 *  longBreak -> In this state (after 4 pomodoros) the watch will count to 15 minutes then restart
 */

enum PomodoroStates {
  pomodoro, shortBreak, longBreak
};

PomodoroStates pomodoroState = pomodoro;

void setup() {
  pinMode(BUTTON, INPUT);

  hourleds.clear(); // Clear all LEDs at init
  minuteleds.clear();

  set_sleep_mode(SLEEP_MODE_STANDBY); // Select standby mode
  sleep_enable();

  hourleds.ring(50); // Startup animation, change LED every 50ms and loop 1 time
  delay(50);
  minuteleds.ring(50);
  delay(50);

  RTC_init(32768); // Go to callback every second
}

void loop() {
  switch(state) {
    case adjust:
      f_adjust();
      break;
      
    case watch:
      f_watch();
      break;
      
    case pomodoroTimer:
      f_pomodoroTimer();
      break;
      
    case sleep:
      f_sleep();
      break;
  }
}

void f_adjust() {
  switch(adjustState) {
    case adjustHour:
      hourleds.set(hours);
      switch(buttonPress(BUTTON, 1000)) {
        case 1: // When you press the button add 1 to hour
          if(hours == 12)
            hours = 1;
          else
            hours++;
          delay(100);
          break;
        case 2: // When you hold down the button switch to adjust minute mode
          minuteleds.set(minutes);
          adjustState = adjustMinute;
          delay(250);
          break;
        default:
          break;
      }
      break;
      
    case adjustMinute:
      minuteleds.set(minutes);
      switch(buttonPress(BUTTON, 1000)) {
        case 1: // When you press the button add 5 to minutes
          if(minutes == 55)
            minutes = 0;
          else
            minutes += 5;
          delay(100); 
          break;
        case 2: // When you hold down the button switch to watch mode
          adjustState = adjustHour;
          state = watch;
          hourleds.clear();
          minuteleds.clear();
          minuteleds.ring(25, 1);
          delay(250);
          break;
        default:
          break;
      }
      break;
  }
}

void f_watch() {
  hourleds.set(hours);  // Set LEDs to current hours and minutes
  minuteleds.set(minutes);

  switch(buttonPress(BUTTON, 1000)) {
    case 1: // When you press the button switch to pomodoro timer mode
      state = pomodoroTimer;
      activeWatchSeconds = 0; // Reset time spent in watch mode
      hourleds.clear();
      minuteleds.clear();
      hourleds.ring(25, 1);
      delay(200); 
      break;
    case 2: // When you hold down the button switch to adjust mode
      state = adjust;
      activeWatchSeconds = 0; // Reset time spent in watch mode
      hourleds.clear();
      minuteleds.clear();
      hourleds.ring(25, 1);
      delay(200);   
      break;
    default:
      break;
  }

  if(activeWatchSeconds >= TIME_UNTIL_SLEEP) {  // If the program is in watch mode for a predetermined ammount of time, enter sleep mode
    activeWatchSeconds = 0; // Reset time spent in watch mode
    wakeUp = false;
    hourleds.clear();
    minuteleds.clear();
    PORTB.PIN1CTRL = PORT_ISC_BOTHEDGES_gc; // Pin change interrupt on pin PB1 to wake up CPU
    state = sleep;
  }
}

void f_pomodoroTimer() {
  minuteleds.pomodoroSet(pomodoroMinutes);
  switch(pomodoroState) {
    case pomodoro:
      if(pomodoroMinutes == 0) {  // Wait until 1 pomodoro (25 min) is over
        if(pomodoroCount == 3) {  // If you have done 4 pomodoros, take a long break
          pomodoroCount = 0;
          pomodoroMinutes = 15;
          pomodoroState = longBreak;
          hourleds.ring(25, 2);
          break;
        }
        else {  // If you haven't done 4 pomodoros, take a short break
          pomodoroCount++;
          pomodoroMinutes = 5;
          pomodoroState = shortBreak;
          hourleds.ring(25, 1);
        }
      }
      break;

    case shortBreak:
      if(pomodoroMinutes == 0) {  // Wait until short break is over
        pomodoroMinutes = 25;
        pomodoroState = pomodoro;
        hourleds.ring(25, 3);
      }
      break;

    case longBreak:
      if(pomodoroMinutes == 0) {  // Wait until long break is over
        pomodoroMinutes = 25;
        pomodoroState = pomodoro;
        hourleds.ring(25, 3);
      }
      break;
  }

  if(digitalRead(BUTTON)) { // When you press the button switch back to normal watch mode
    state = watch;
    hourleds.clear();
    minuteleds.clear();
    minuteleds.ring(25, 1);
    pomodoroMinutes = 25;
    pomodoroSeconds = 0;
    pomodoroCount = 0;
    delay(200); 
  }
}

void f_sleep() {
  while(!wakeUp) {  // Loop until button is pressed
    sleep_cpu();  // Enter Stand By mode
  }
  
  hourleds.ring(50); // Wake up animation, change LED every 50ms and loop 1 time
  delay(35);
  minuteleds.ring(50);
  delay(35);
  state = watch;
}

uint8_t buttonPress(uint8_t buttonPin, uint16_t duration) {
  uint32_t startTime = 0;

  if (digitalRead(buttonPin)) {
    startTime = millis();

    while (digitalRead(buttonPin)) {  // While the button is pressed
      if (millis() - startTime >= duration) { // If the button is hold as long or longer than given, return 2
        return 2;
      }
    }
    return 1; // If the button is pressed but not held down long enough, return 1
  }
  
  return 0; // If the button isnt pressed return 0
}

void RTC_init(uint16_t RTCdelay) {     
  RTC.CLKSEL = RTC_CLKSEL_INT32K_gc;  // 32.768kHz Internal Crystal Oscillator (INT32K) 

  while (RTC.STATUS > 0); // Wait for all register to be synchronized
  RTC.PER = RTCdelay; // Set period for delay
  RTC.INTCTRL |= RTC_OVF_bm;  // Enable overflow Interrupt which will trigger ISR
  RTC.CTRLA = RTC_RTCEN_bm  // Enable: enabled 
  | RTC_RUNSTDBY_bm;  // Run In Standby: enabled
}

ISR(RTC_CNT_vect) {
  RTC.INTFLAGS = RTC_OVF_bm;  // Clear flag

  if(state != adjust) {
    seconds++;  // Count the seconds, minutes and hours in any state but adjust
    if(seconds == 60) {
      seconds = 0;
      minutes++;
    }
    if(minutes == 60) {
      minutes = 0;
      hours++;
    }
    if(hours == 13) {
      hours = 1;
    }    
  }

  if(state == watch)
    activeWatchSeconds++;

  if(state == pomodoroTimer) {  // If the watch is in pomodoro mode, count down every minute
    pomodoroSeconds++;
    if(pomodoroSeconds == 60) {
      pomodoroSeconds = 0;
      pomodoroMinutes--;
    }
  }
}

ISR(PORTB_PORT_vect) {  // When the CPU wakes up, this function will be called
  PORTB.PIN1CTRL &= ~PORT_ISC_gm; // Disable interrupt, keep it disabled until CPU goes in standby mode
  wakeUp = true;
  PORTB.INTFLAGS = PIN1_bm; // Clear flag
}
