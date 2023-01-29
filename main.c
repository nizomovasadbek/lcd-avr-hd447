#include "main.h"

int main(void){
	LCDControlDirection |= (1 << ReadWrite) | (1 << RSPin) | (1 << Enable);

	_delay_ms(15);

	lcd_send(0x01, command);
	_delay_ms(2);
	lcd_send(0x38, command);
	_delay_us(50);
	lcd_send(0x0F, command);
	_delay_us(50);

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
