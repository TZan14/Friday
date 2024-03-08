/* 
 * Title     : Core I/O Library for AVR based Microcontrollers
 * Developer : Min Thet Zan
 * Company   : Friday Electronics Ltd.
 * Version   : 1.0.0
 * Date      : 8 March 2024   
 * 
 */
 
#ifndef FRIDAY_IO_HPP
#define FRIDAY_IO_HPP

//Clock Speed Definition
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
  #define CPU_CLK 16000000UL // Clock speed for Arduino Uno
//Reserve for other AVR microcontroller
#endif

//Macros
#define DDRB   *(volatile uint8_t*)0x24
#define PORTB  *(volatile uint8_t*)0x25
#define TCCR0A *(volatile uint8_t*)0x44
#define TCCR0B *(volatile uint8_t*)0x45
#define OCR0A  *(volatile uint8_t*)0x47
#define TIFR0  *(volatile uint8_t*)0x35

//Require data
bool in = 0, IN = 0, In = 0, off = 0, OFF = 0, Off = 0; //Input mode & Off state
bool out = 1, OUT = 1, Out = 1, on = 1, ON = 1, On = 1; //Output mode & On state

//Sleep Function 
//Using timer 0
void sleep(uint16_t microseconds) {

  TCCR0A = 0x02; // Set CTC mode
  OCR0A = (CPU_CLK / (64.0 * 1000)) - 1;
  TCCR0B |= 0x03; // Clock/64 Prescaler
  int time_count = 0;
  for (time_count = 0; time_count < microseconds; time_count++) {
    while ((TIFR0 & 0x02) == 0) {
      ;; // Wait for the compare match flag
    }
    TIFR0 |= 0x02; // Clear the compare match flag
  }
}

///// PINS /////
//Mode setup

///// FOR Arduino Uno, Arduino Nano & ATmega328P Boards /////
#ifdef __AVR_ATmega328P__
void set_pin(uint8_t pin, bool mode) {
  switch (pin) {
    //DDRB0 - DDRB5
    case 13: case 12: case 11: case 10: case 9: case 8:
      uint8_t bit_position = pin - 8;
      (mode) ? DDRB |= (1 << bit_position) : DDRB |= (0 << bit_position);
      break;
    //DDRD0 - DDRD5
    case 7: case 6: case 5: case 4: case 3: case 2: case 1:
      uint8_t bit_position_1 = pin - 2;
      (mode) ? DDRD |= (1 << bit_position_1) : DDRD |= (0 << bit_position_1);
      break;
  }
}

void pin_write(uint8_t pin, bool state) {
  switch (pin) {
    //PORTB0 - PORTB5
    case 13: case 12: case 11: case 10: case 9: case 8:
      uint8_t bit_position = pin - 8;
      (state) ? PORTB |= (1 << bit_position) : PORTB &= (0 << bit_position);
      break;
    //DDRD0 - DDRD5
    case 7: case 6: case 5: case 4: case 3: case 2: case 1:
      uint8_t bit_position_1 = pin - 2;
      (state) ? PORTD |= (1 << bit_position_1) : PORTD &= (0 << bit_position_1);
      break;
  }
}
#endif // ATmega328P function definitions end here
#endif // End of the program 
