#include <Arduino.h>
#include "Led_Classes.h"
  
void HourLeds::set(uint8_t hour) {
  switch(hour) {
    case 1:
      PORTC.DIRSET = PIN0_bm | PIN1_bm;
      PORTC.DIRCLR = PIN2_bm | PIN3_bm;

      PORTC.OUTSET = PIN0_bm | PIN2_bm;
      PORTC.OUTCLR = PIN1_bm | PIN3_bm;
      break;

    case 2:
      PORTC.DIRCLR = PIN0_bm | PIN3_bm;
      PORTC.DIRSET = PIN1_bm | PIN2_bm;

      PORTC.OUTSET = PIN2_bm;
      PORTC.OUTCLR = PIN3_bm | PIN0_bm | PIN1_bm;
      break;

    case 3:
      PORTC.DIRCLR = PIN0_bm | PIN3_bm;
      PORTC.DIRSET = PIN1_bm | PIN2_bm;

      PORTC.OUTCLR = PIN0_bm | PIN2_bm | PIN3_bm;
      PORTC.OUTSET = PIN1_bm;
      break;

    case 4:
      PORTC.DIRCLR = PIN1_bm | PIN0_bm;
      PORTC.DIRSET = PIN2_bm | PIN3_bm;

      PORTC.OUTCLR = PIN2_bm | PIN0_bm | PIN1_bm;
      PORTC.OUTSET = PIN3_bm;
      break;

    case 5:
      PORTC.DIRCLR = PIN1_bm | PIN0_bm;
      PORTC.DIRSET = PIN2_bm | PIN3_bm;
      
      PORTC.OUTCLR = PIN1_bm | PIN0_bm | PIN3_bm;
      PORTC.OUTSET = PIN2_bm;
      break;

    case 6:
      PORTC.DIRCLR = PIN1_bm | PIN3_bm;
      PORTC.DIRSET = PIN2_bm | PIN0_bm;

      PORTC.OUTCLR = PIN1_bm | PIN0_bm | PIN3_bm;
      PORTC.OUTSET = PIN2_bm;
      break;

    case 7:
      PORTC.DIRSET = PIN0_bm | PIN2_bm;
      PORTC.DIRCLR = PIN1_bm | PIN3_bm;

      PORTC.OUTSET = PIN0_bm;
      PORTC.OUTCLR = PIN1_bm | PIN2_bm | PIN3_bm;
      break;

    case 8:
      PORTC.DIRCLR = PIN0_bm | PIN2_bm;
      PORTC.DIRSET = PIN1_bm | PIN3_bm;

      PORTC.OUTCLR = PIN0_bm | PIN2_bm | PIN1_bm;
      PORTC.OUTSET = PIN3_bm;
      break;

    case 9:
      PORTC.DIRCLR = PIN0_bm | PIN2_bm;
      PORTC.DIRSET = PIN1_bm | PIN3_bm;

      PORTC.OUTCLR = PIN0_bm | PIN2_bm | PIN3_bm;
      PORTC.OUTSET = PIN1_bm;
      break;

    case 10:
      PORTC.DIRSET = PIN0_bm | PIN3_bm;
      PORTC.DIRCLR = PIN1_bm | PIN2_bm;

      PORTC.OUTCLR = PIN2_bm | PIN0_bm | PIN1_bm;
      PORTC.OUTSET = PIN3_bm;
      break;

    case 11:
      PORTC.DIRCLR = PIN2_bm | PIN1_bm;
      PORTC.DIRSET = PIN3_bm | PIN0_bm;

      PORTC.OUTSET = PIN0_bm;
      PORTC.OUTCLR = PIN2_bm | PIN1_bm | PIN3_bm;
      break;

    case 0:
    case 12:
      PORTC.DIRSET = PIN1_bm | PIN0_bm;
      PORTC.DIRCLR = PIN2_bm | PIN3_bm;

      PORTC.OUTSET = PIN1_bm;
      PORTC.OUTCLR = PIN2_bm | PIN3_bm | PIN0_bm;
      break;

    default:
      HourLeds::clear();
      break;
  }
}

void HourLeds::clear() {
  PORTC.DIRSET = PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm;
  PORTC.OUTCLR = PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm;
}

void HourLeds::ring(uint16_t speed, uint8_t loops=1) {
  for(uint8_t i = 0; i < loops; i++) {
    for(uint8_t j = 0; j < 13; j++) {
      HourLeds::set(j);
      delay(speed);
    } 
  }
  HourLeds::clear();
}



void MinuteLeds::set(uint8_t minute) {
  switch(minute) {
    case 60:
    case 0 ... 4:
      PORTA.DIRSET = PIN4_bm | PIN5_bm;
      PORTB.DIRCLR = PIN2_bm | PIN0_bm;

      PORTA.OUTSET = PIN4_bm;
      PORTA.OUTCLR = PIN5_bm;
      PORTB.OUTCLR = PIN2_bm | PIN0_bm;
      break;

    case 10 ... 14:
      PORTA.DIRCLR = PIN4_bm;
      PORTA.DIRSET = PIN5_bm;
      PORTB.DIRSET = PIN2_bm;
      PORTB.DIRCLR = PIN0_bm;

      PORTA.OUTCLR = PIN4_bm;
      PORTA.OUTSET = PIN5_bm;
      PORTB.OUTCLR = PIN2_bm | PIN0_bm;
      break;

    case 15 ... 19:
      PORTA.DIRCLR = PIN4_bm;
      PORTA.DIRSET = PIN5_bm;
      PORTB.DIRSET = PIN2_bm;
      PORTB.DIRCLR = PIN0_bm;

      PORTA.OUTCLR = PIN4_bm | PIN5_bm;
      PORTB.OUTSET = PIN2_bm;
      PORTB.OUTCLR = PIN0_bm;
      break;
      
    case 20 ... 24:
      PORTA.DIRCLR = PIN4_bm | PIN5_bm;
      PORTB.DIRSET = PIN2_bm | PIN0_bm;

      PORTA.OUTCLR = PIN4_bm | PIN5_bm;
      PORTB.OUTSET = PIN2_bm;
      PORTB.OUTCLR = PIN0_bm;
      break;
      
    case 25 ... 29:
      PORTA.DIRCLR = PIN4_bm | PIN5_bm;
      PORTB.DIRSET = PIN2_bm | PIN0_bm;

      PORTA.OUTCLR = PIN4_bm | PIN5_bm;
      PORTB.OUTCLR = PIN2_bm;
      PORTB.OUTSET = PIN0_bm;
      break;

    case 30 ... 34:
      PORTA.DIRSET = PIN4_bm;
      PORTA.DIRCLR = PIN5_bm;
      PORTB.DIRSET = PIN2_bm;
      PORTB.DIRCLR = PIN0_bm;

      PORTA.OUTSET = PIN4_bm;
      PORTA.OUTCLR = PIN5_bm;
      PORTB.OUTCLR = PIN2_bm | PIN0_bm;
      break;

    case 35 ... 39:
      PORTA.DIRSET = PIN4_bm;
      PORTA.DIRCLR = PIN5_bm;
      PORTB.DIRSET = PIN2_bm;
      PORTB.DIRCLR = PIN0_bm;

      PORTA.OUTCLR = PIN4_bm | PIN5_bm;
      PORTB.OUTSET = PIN2_bm;
      PORTB.OUTCLR = PIN0_bm;
      break;

    case 40 ... 44:
      PORTA.DIRCLR = PIN4_bm;
      PORTA.DIRSET = PIN5_bm;
      PORTB.DIRCLR = PIN2_bm;
      PORTB.DIRSET = PIN0_bm;

      PORTA.OUTCLR = PIN4_bm;
      PORTA.OUTSET = PIN5_bm;
      PORTB.OUTCLR = PIN2_bm | PIN0_bm;
      break;

    case 45 ... 49:
      PORTA.DIRCLR = PIN4_bm;
      PORTA.DIRSET = PIN5_bm;
      PORTB.DIRCLR = PIN2_bm;
      PORTB.DIRSET = PIN0_bm;

      PORTA.OUTCLR = PIN4_bm | PIN5_bm;
      PORTB.OUTCLR = PIN2_bm;
      PORTB.OUTSET = PIN0_bm;
      break;

    case 50 ... 54:
      PORTA.DIRSET = PIN4_bm;
      PORTA.DIRCLR = PIN5_bm;
      PORTB.DIRCLR = PIN2_bm;
      PORTB.DIRSET = PIN0_bm;

      PORTA.OUTSET = PIN4_bm;
      PORTA.OUTCLR = PIN5_bm;
      PORTB.OUTCLR = PIN2_bm;
      PORTB.OUTCLR = PIN0_bm;
      break;

    case 55 ... 59:
      PORTA.DIRSET = PIN4_bm;
      PORTA.DIRCLR = PIN5_bm;
      PORTB.DIRCLR = PIN2_bm;
      PORTB.DIRSET = PIN0_bm;

      PORTA.OUTCLR = PIN4_bm | PIN5_bm;
      PORTB.OUTCLR = PIN2_bm;
      PORTB.OUTSET = PIN0_bm;
      break;

    case 5 ... 9:
      PORTA.DIRSET = PIN4_bm | PIN5_bm;
      PORTB.DIRCLR = PIN2_bm | PIN0_bm;

      PORTA.OUTCLR = PIN4_bm;
      PORTA.OUTSET = PIN5_bm;
      PORTB.OUTCLR = PIN2_bm;
      PORTB.OUTCLR = PIN0_bm;
      break;

    default:
      MinuteLeds::clear();
      break;
  }
}

void MinuteLeds::clear() {
  PORTA.DIRSET = PIN4_bm | PIN5_bm;
  PORTB.DIRSET = PIN2_bm | PIN0_bm;

  PORTA.OUTCLR = PIN4_bm | PIN5_bm;
  PORTB.OUTCLR = PIN2_bm | PIN0_bm;
}

void MinuteLeds::pomodoroSet(uint8_t minute) {
  const uint8_t wait = 3;
  
  switch(minute) {
    case 21 ... 25:
      for(uint8_t i = 0; i < 6; i++) {
        MinuteLeds::set(i*5);
        delay(wait);
      }
      break;
    
    case 16 ... 20:
      for(uint8_t i = 0; i < 5; i++) {
        MinuteLeds::set(i*5);
        delay(wait);
      }
      break;

    case 11 ... 15:
      for(uint8_t i = 0; i < 4; i++) {
        MinuteLeds::set(i*5);
        delay(wait);
      }
      break;

    case 6 ... 10:
      for(uint8_t i = 0; i < 3; i++) {
        MinuteLeds::set(i*5);
        delay(wait);
      }
      break;

    case 2 ... 5:
      for(uint8_t i = 0; i < 2; i++) {
        MinuteLeds::set(i*5);
        delay(wait);
      }
      break;

    case 0 ... 1:
      MinuteLeds::set(0);
      break;
  }
}

void MinuteLeds::ring(uint16_t speed, uint8_t loops=1) {
  for(int i = 0; i < loops; i++) {
    for(int j = 0; j < 13; j++) {
      MinuteLeds::set(j*5);
      delay(speed);
    } 
  }
  MinuteLeds::clear();
}
