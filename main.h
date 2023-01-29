#ifndef MAIN_H
#define MAIN_H

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#define LCDControlPort PORTD
#define LCDDataPort PORTB
#define LCDControlPin PIND
#define LCDDataPin PINB
#define LCDControlDirection DDRD
#define LCDDataDirection DDRB
#define RSPin 0x02
#define ReadWrite 0x07
#define Enable 0x05

void lcd_send(char, void (*)());
void command(void);
void data(void);
void render(void);
void checkBusy(void);

#endif
