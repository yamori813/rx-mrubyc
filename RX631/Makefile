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

MRBCOBJ = alloc.o c_array.o c_hash.o c_math.o c_numeric.o c_object.o c_range.o c_string.o class.o console.o error.o global.o keyvalue.o load.o mrblib.o rrt0.o symbol.o value.o vm.o
CROSS_CFLAGS += -std=c99 -I. -I../mrubyc/src
CROSS_CFLAGS += -DMRBC_NO_TIMER

rx631.mot:	rx631.elf
	$(CROSS_OBJCOPY) rx631.elf -O srec -I elf32-rx-be-ns $@
	@cksum -o 3 $@ | awk '{printf "CRC-32 : %08X\n", $$1}'

rx631.elf:	$(OBJS) $(MRBCOBJ)
	$(CROSS_CC) $(CROSS_LIBS) $(CROSS_LDFLAGS) -o $@ $(OBJS) $(MRBCOBJ)

.c.o:
	$(CROSS_CC) $(CROSS_CFLAGS) -c $<

start.o: start.S
	$(CROSS_CC) $(ASDEF) -c start.S

clean:
	rm -rf *.o *.elf *.mot

alloc.o : ../mrubyc/src/alloc.c
c_array.o : ../mrubyc/src/c_array.c
c_hash.o : ../mrubyc/src/c_hash.c
c_math.o : ../mrubyc/src/c_math.c
c_numeric.o : ../mrubyc/src/c_numeric.c
c_object.o : ../mrubyc/src/c_object.c
c_range.o : ../mrubyc/src/c_range.c
c_string.o : ../mrubyc/src/c_string.c
class.o : ../mrubyc/src/class.c
console.o : ../mrubyc/src/console.c
error.o : ../mrubyc/src/error.c
global.o : ../mrubyc/src/global.c
keyvalue.o : ../mrubyc/src/keyvalue.c
load.o : ../mrubyc/src/load.c
mrblib.o : ../mrubyc/src/mrblib.c
rrt0.o : ../mrubyc/src/rrt0.c
symbol.o : ../mrubyc/src/symbol.c
value.o : ../mrubyc/src/value.c
vm.o : ../mrubyc/src/vm.c
