# Nahrání firmware

Procesory ve stavebnicích už mají program nahraný.

Kód je určený pro Arduino IDE. Pro nahrání do procesoru je nejprve potřeba nainstalovat MicroCore jádro pro ATtiny13 ([https://github.com/MCUdude/MicroCore](https://github.com/MCUdude/MicroCore) ). Žádné další knihovny nejsou potřeba.

Po nainstalování vyber v menu Tools (Nástroje) následující možnosti:

| Možnost | Hodnota |
| --- | --- |
| Board | ATTiny13 |
| BOD | 1.8V |
| LTO | Enabled |
| Clock | 1.2MHz internal OSC |

Procesor ATtiny13 nemá bootloader, takže je potřeba použít programátor (např. AVRisp nebo USBasp). Po připojení programátoru k ISP konektoru J1 v Arduino IDE zvolte možnost "Tools / Burn bootloader" a poté "Sketch / Upload"

---

Příkazová řádka pro avrdude a programátor USBasp:

```
avrdude -pattiny13 -cusbasp -B10 -Pusb -e -Ulock:w:0x3f:m -Uhfuse:w:0xfd:m -Ulfuse:w:0x2A:m -Uflash:w:dice.ino_attiny13a_1200000L.hex:i -Ueeprom:w:`hexdump -n 2 -e '2/1 "0x%02x,"' /dev/random`:m -Ulock:w:0x3e:m
```

bez nastavení generátoru náhodných čísel:

```
avrdude -pattiny13 -cusbasp -B10 -Pusb -e -Ulock:w:0x3f:m -Uhfuse:w:0xfd:m -Ulfuse:w:0x2A:m -Uflash:w:dice.ino_attiny13a_1200000L.hex:i -Ulock:w:0x3e:m
```
