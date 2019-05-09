
ISR (PCINT0_vect) {
  // disable interrupt enable flag
  GIMSK &= ~(_BV(PCIE));
}

void sleepEnter() {
  cli();

  wdt_reset();

  // enable iterrupt on change and clear interrupt flag
  GIFR = _BV(PCIF);
  GIMSK |= _BV(PCIE);

  // enable possibility to enter sleep mode
  sleep_enable();
  // disable BOD - needs to be done exactly before sleep
  sleep_bod_disable();
  // enable interrupts (on change interrupt) to wake the cpu
  sei();
  // go to sleep finally
  sleep_cpu();
  // disable possibility to enter sleep mode
  sleep_disable();
  // enable interrupts (just for sure)
  sei();
}

void sleepSetup(const uint8_t pcmsk) {
  // select sleep mode and configure on-change interrupt source
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  PCMSK = pcmsk;
}
