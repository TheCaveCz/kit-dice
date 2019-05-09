
uint16_t randomNumber = 0;

uint16_t lfsr16Next(const uint16_t n) {
  return (n >> 0x01U) ^ (-(n & 0x01U) & 0xB400U);
}

uint16_t randomN(const uint16_t limit) {
  return (randomNumber = lfsr16Next(randomNumber)) % limit;
}

void randomSetup() {
  randomNumber = lfsr16Next(eeprom_read_word(0) ^ 0x453f);
  eeprom_write_word(0, randomNumber);
}
