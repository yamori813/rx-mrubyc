#
# BSD makefile for rx-mrubyc
#

PREFIX = rx-elf

CROSS_CC = $(PREFIX)-gcc
CROSS_AS = $(PREFIX)-as
CROSS_LD = $(PREFIX)-ld
CROSS_OBJCOPY = $(PREFIX)-objcopy
CROSS_SIZE = $(PREFIX)-size

CROSS_LIBS = -lc -lgcc

CROSS_CFLAGS = -O2 -ffunction-sections -fdata-sections -Wstack-usage=200 -mcpu=rx200 -misa=v1 -mlittle-endian-data -nofpu
CROSS_CFLAGS += -I../common
CROSS_LDFLAGS = -T linker_script.ld -nostartfiles

OBJS = main.o
OBJS += xprintf.o e2flash.o monitor.o
OBJS += r_init_clock.o sci.o
OBJS += start.o hwinit.o inthandler.o vects.o

main.mot:	main.elf
	$(CROSS_OBJCOPY) main.elf -O srec -I elf32-rx-be-ns $@
	@cksum -o 3 $@ | awk '{printf "CRC-32 : %08X\n", $$1}'

include ../mrubyc.mk

main.elf:	$(OBJS) $(MRBCOBJ)
	$(CROSS_CC) $(CROSS_LIBS) $(CROSS_LDFLAGS) -o $@ $(OBJS) $(MRBCOBJ)
	$(CROSS_SIZE) $@

.c.o:
	$(CROSS_CC) $(CROSS_CFLAGS) -c $<

start.o: start.S
	$(CROSS_CC) $(ASDEF) -c start.S

clean:
	rm -rf *.o *.elf *.mot

xprintf.o : ../common/xprintf.c
e2flash.o : ../common/e2flash.c
monitor.o : ../common/monitor.c
