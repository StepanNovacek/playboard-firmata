// Redefinition of Arduino Zero from Firmata - so we can use Firmata without modifications
// Pin 25,26 LEDs
// Pin 30,31 Buttons

#define TOTAL_ANALOG_PINS       6
#define TOTAL_PINS              32
#define TOTAL_PORTS             4

#define VERSION_BLINK_PIN       25

#define IS_PIN_DIGITAL(p)       (((p) >= 0 && (p) <= 19) || ((p) == 25) || ((p) == 26) || ((p) == 30) || ((p) == 31))
#define IS_PIN_ANALOG(p)        ((p) >= 14 && (p) < 14 + TOTAL_ANALOG_PINS)
#define IS_PIN_PWM(p)           digitalPinHasPWM(p)
#define IS_PIN_I2C(p)           ((p) == 20 || (p) == 21) // SDA = 20, SCL = 21
#define IS_PIN_SPI(p)           ((p) == SS || (p) == MOSI || (p) == MISO || (p) == SCK) // SS = A2
#define IS_PIN_SERIAL(p)        ((p) == 0 || (p) == 1)
#define PIN_TO_DIGITAL(p)       (p)
#define PIN_TO_ANALOG(p)        ((p) - 14)
#define PIN_TO_PWM(p)           PIN_TO_DIGITAL(p)

/*==============================================================================
 * readPortPB() - Read an 8 bit port
 *============================================================================*/

static inline unsigned char readPortPB(byte, byte) __attribute__((always_inline, unused));
static inline unsigned char readPortPB(byte port, byte bitmask)
{
  unsigned char out = 0, pin = port * 8;
  if (IS_PIN_DIGITAL(pin + 0) && (bitmask & 0x01) && digitalRead(PIN_TO_DIGITAL(pin + 0))) out |= 0x01;
  if (IS_PIN_DIGITAL(pin + 1) && (bitmask & 0x02) && digitalRead(PIN_TO_DIGITAL(pin + 1))) out |= 0x02;
  if (IS_PIN_DIGITAL(pin + 2) && (bitmask & 0x04) && digitalRead(PIN_TO_DIGITAL(pin + 2))) out |= 0x04;
  if (IS_PIN_DIGITAL(pin + 3) && (bitmask & 0x08) && digitalRead(PIN_TO_DIGITAL(pin + 3))) out |= 0x08;
  if (IS_PIN_DIGITAL(pin + 4) && (bitmask & 0x10) && digitalRead(PIN_TO_DIGITAL(pin + 4))) out |= 0x10;
  if (IS_PIN_DIGITAL(pin + 5) && (bitmask & 0x20) && digitalRead(PIN_TO_DIGITAL(pin + 5))) out |= 0x20;
  if (IS_PIN_DIGITAL(pin + 6) && (bitmask & 0x40) && digitalRead(PIN_TO_DIGITAL(pin + 6))) out |= 0x40;
  if (IS_PIN_DIGITAL(pin + 7) && (bitmask & 0x80) && digitalRead(PIN_TO_DIGITAL(pin + 7))) out |= 0x80;
  return out;
}

/*==============================================================================
 * readPortPB() - Write an 8 bit port, only touch pins specified by a bitmask
 *============================================================================*/

static inline unsigned char writePortPB(byte, byte, byte) __attribute__((always_inline, unused));
static inline unsigned char writePortPB(byte port, byte value, byte bitmask)
{
  byte pin = port * 8;
  if ((bitmask & 0x01)) digitalWrite(PIN_TO_DIGITAL(pin + 0), (value & 0x01));
  if ((bitmask & 0x02)) digitalWrite(PIN_TO_DIGITAL(pin + 1), (value & 0x02));
  if ((bitmask & 0x04)) digitalWrite(PIN_TO_DIGITAL(pin + 2), (value & 0x04));
  if ((bitmask & 0x08)) digitalWrite(PIN_TO_DIGITAL(pin + 3), (value & 0x08));
  if ((bitmask & 0x10)) digitalWrite(PIN_TO_DIGITAL(pin + 4), (value & 0x10));
  if ((bitmask & 0x20)) digitalWrite(PIN_TO_DIGITAL(pin + 5), (value & 0x20));
  if ((bitmask & 0x40)) digitalWrite(PIN_TO_DIGITAL(pin + 6), (value & 0x40));
  if ((bitmask & 0x80)) digitalWrite(PIN_TO_DIGITAL(pin + 7), (value & 0x80));
  return 1;
}
