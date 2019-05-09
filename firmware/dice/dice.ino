/*
   Dice kit firmware

   The Cave, 2019
   https://thecave.cz

   Licensed under MIT License (see LICENSE file for details)

   using MicroCore (https://github.com/MCUdude/MicroCore)

   Board: ATTiny13
   BOD: 1.8V
   LTO: Enabled
   Clock: 1.2MHz internal OSC

*/
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>


#define PIN_BTN 4
#define NUMBER_EMPTY 6

const uint8_t numbers[7] PROGMEM = {
  0b1000,
  0b0100,
  0b1100,
  0b0101,
  0b1101,
  0b0111,
  0b0000,
};


void setup() {
  // turn off adc/wdt to save power
  WDTCR = 0;
  ADCSRA = 0;

  // wake up when PIN_BTN state changes
  sleepSetup(_BV(PIN_BTN));

  randomSetup();
}

uint8_t buttonRead() {
  return !(PINB & _BV(PIN_BTN));
}

void showNumber(const uint8_t n) {
  PORTB = pgm_read_byte(numbers + n) | _BV(PIN_BTN);
}

void goToSleep() {
  // all pins as inputs
  DDRB = 0;
  PORTB = _BV(PIN_BTN);
  // enter sleep
  sleepEnter();
  // set led pins as outputs, set button as input_pullup
  DDRB = 0b01111;
}

void loop() {
  goToSleep();
  if (!buttonRead()) return;

  uint8_t d = 50;
  uint8_t cnt = 20;
  uint8_t n = 0, n1 = 0;
  while (cnt--) {
    while (n == n1) {
      n1 = randomN(6);
    }
    n = n1;
    showNumber(n);
    delay(d);
    d += 5;
  }

  delay(1000);

  cnt = 3;
  while (cnt--) {
    showNumber(NUMBER_EMPTY);
    delay(250);
    showNumber(n);
    delay(250);
  }
}
