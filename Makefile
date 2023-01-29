DEVICE=atmega32
CC=avr-gcc
BIN=main.bin
HEX_FILE=main.hex
CONVERT=avr-objcopy -j .text -j .data -O ihex

all: $(BIN)

%.bin: %.c
	$(CC) -mmcu=$(DEVICE) -Os $^ -o $@
	$(CONVERT) $@ $(HEX_FILE)
	
clean:
	$(RM) $(BIN)
	$(RM) $(HEX_FILE)