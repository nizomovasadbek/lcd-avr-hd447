DEVICE=atmega32
SRC=$(wildcard *.c)
BINS=$(SRC:.c=.o)
CC=avr-gcc
FLAGS=-g -Wall -c -Os

all: $(BINS)

%.o: %.c
	$(CC) -mmcu=$(DEVICE) -Os $^ -o $@
	
clean:
	$(RM) $(BINS)