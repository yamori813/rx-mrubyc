#
#
#

PREFIX = rx-elf

CROSS_CC = $(PREFIX)-gcc
CROSS_AS = $(PREFIX)-as
CROSS_LD = $(PREFIX)-ld
CROSS_OBJCOPY = $(PREFIX)-objcopy

CROSS_LIBS = -lc -lgcc

CROSS_CFLAGS = -O2 -ffunction-sections -fdata-sections -mcpu=rx600 -misa=v1 -mlittle-endian-data -nofpu
CROSS_CFLAGS += -DRELEASE -DGRCITRUS
CROSS_LDFLAGS = -T linker_script.ld -nostartfiles

OBJS = rx631.o
OBJS += start.o hwinit.o inthandler.o vects.o
OBJS += usb_core.o usb_hal.o usb_cdc.o usbdescriptors.o util.o

rx631.mot:	rx631.elf
	$(CROSS_OBJCOPY) rx631.elf -O srec -I elf32-rx-be-ns $@
	@cksum -o 3 $@ | awk '{printf "CRC-32 : %08X\n", $$1}'

rx631.elf:	$(OBJS)
	$(CROSS_CC) $(CROSS_LIBS) $(CROSS_LDFLAGS) -o $@ $(OBJS)

.c.o:
	$(CROSS_CC) $(CROSS_CFLAGS) -c $<

start.o: start.S
	$(CROSS_CC) $(ASDEF) -c start.S

clean:
	rm -rf *.o *.elf *.mot
