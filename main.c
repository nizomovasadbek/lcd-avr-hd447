#include "led.h"

int main(void){
	LCDControlDirection |= (1 << ReadWrite) | (1 << RSPin) | (1 << Enable);

	_delay_ms(15);

	lcd_send(0x01, command);
	_delay_ms(2);
	lcd_send(0x38, command);
	_delay_us(50);
	lcd_send(0x0E, command);
	_delay_us(50);

	unsigned char c;
	char isEnd = 0x00;
	unsigned int addrCnt = 0x00;

	while(true){
		if(!isEnd){
			c = eeprom_read_byte((uint8_t*) addrCnt);
			if(c == 0xff) {
				isEnd = 0x01;
				continue;
			}
			lcd_send(c, data);
			_delay_ms(200);
			addrCnt++;
		}
	}

	return 0;
}

void checkBusy(){
	LCDDataDirection = 0x00;
	LCDControlPort |= (1 << ReadWrite);
	LCDControlPort &= ~(1 << RSPin);

	while(LCDDataPin & 0x80){
		render();
	}

	LCDDataDirection = 0xff;
}

void render(){
	LCDControlPort |= (1 << Enable);
	asm volatile ("nop");
	asm volatile ("nop");
	LCDControlPort &= ~(1 << Enable);
}

void lcd_send(char data, void (*method)()){
	checkBusy();
	LCDDataPort = data;
	LCDControlPort &= ~(1 << ReadWrite);
	method();
	render();
	LCDDataPort = 0x00;
}

void data(){
	LCDControlPort |= (1 << RSPin);
}

void command(){
	LCDControlPort &= ~(1 << RSPin);
}

void sendString(char* string){
	while(*string > 0){
		lcd_send(*string++, data);
	}
}

void sendStringWithEffect(char* string){
	while(*string>0){
		lcd_send(*string++, data);
		_delay_ms(250);
	}
}
