NAME = main

OBJECTS = motor.o distance.o path.o sensor.o led_lights.o interrupt_handlers.o odometer.o
LIBPI_STUDENT_MODULES = #timer.o gpio.o printf.o malloc.o backtrace.o

CS107E=../../cs107e.github.io

#CFLAGS  = -I$(CS107E)/libpi/include -g -Wall -Werror -Wpointer-arith 
CFLAGS  = -I$(CS107E)/libpi/include -g -Wall -Wpointer-arith
CFLAGS += -Og -std=c99 -ffreestanding 
CFLAGS += -mapcs-frame -fno-omit-frame-pointer -mpoke-function-name
LDFLAGS = -nostdlib -T memmap -L$(CS107E)/libpi/lib
REFERENCE_WITH_PATH = $(patsubst %.o,$(CS107E)/libpi/modules/%.o,$(LIBPI_REFERENCE_MODULES))
LDLIBS = -lpi -lgcc
LIBPI_SOURCES = abort.c armtimer.c font.c gpioevent.c gpioextra.c interrupts.c mailbox.c ps2.c reboot.c strtol.c uart.c
LIBPI_ALL = $(LIBPI_STUDENT_MODULES) $(REFERENCE_WITH_PATH) $(LIBPI_SOURCES:.c=.o) $(LIBPI_ASM_SOURCES:.s=.o)
LIBPI_ASM_SOURCES = register.s vectors.s

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
