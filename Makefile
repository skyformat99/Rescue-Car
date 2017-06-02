NAME = main

OBJECTS = tof.o
#LIBPI_STUDENT_MODULES = timer.o gpio.o printf.o malloc.o backtrace.o

CS107E=../cs107e.github.io

#CFLAGS  = -I$(CS107E)/libpi/include -g -Wall -Werror -Wpointer-arith 
CFLAGS  = -I$(CS107E)/libpi/include -g -Wall -Wpointer-arith
CFLAGS += -Og -std=c99 -ffreestanding 
CFLAGS += -mapcs-frame -fno-omit-frame-pointer -mpoke-function-name
LDFLAGS = -nostdlib -T memmap -L$(CS107E)/libpi/lib
LDLIBS = -lpi -lgcc


all : $(NAME).bin $(LIBPI_STUDENT_MODULES)

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: %.o $(OBJECTS) start.o cstart.o $(LIBPI_STUDENT_MODULES)
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-as $< -o $@

%.list: %.o
	arm-none-eabi-objdump -d $< > $@

install: $(NAME).bin
	rpi-install.py -s $<

test: test.bin
	rpi-install.py -s $<

clean:
	rm -f *.o *.bin *.elf *.list *~

.PHONY: all clean install test

.PRECIOUS: %.o %.elf