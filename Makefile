#
#
#

PREFIX = rx-elf

CROSS_CC = $(PREFIX)-gcc
CROSS_AS = $(PREFIX)-as
CROSS_LD = $(PREFIX)-ld
CROSS_OBJCOPY = $(PREFIX)-objcopy
CROSS_SIZE = $(PREFIX)-size

CROSS_LIBS = -lc -lgcc

#CROSS_CFLAGS = -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=200 -mcpu=rx200 -misa=v1 -mlittle-endian-data -nofpu
CROSS_CFLAGS = -O2 -ffunction-sections -fdata-sections -Wstack-usage=200 -mcpu=rx200 -misa=v1 -mlittle-endian-data -nofpu
CROSS_LDFLAGS = -T linker_script.ld -nostartfiles

OBJS = main.o
OBJS += r_init_clock.o sci.o
OBJS += start.o hwinit.o inthandler.o vects.o

MRBCOBJ = mrubyc/src/alloc.o mrubyc/src/c_array.o mrubyc/src/c_hash.o mrubyc/src/c_math.o mrubyc/src/c_numeric.o mrubyc/src/c_object.o mrubyc/src/c_range.o mrubyc/src/c_string.o mrubyc/src/class.o mrubyc/src/console.o mrubyc/src/error.o mrubyc/src/global.o mrubyc/src/keyvalue.o mrubyc/src/load.o mrubyc/src/mrblib.o mrubyc/src/rrt0.o mrubyc/src/symbol.o mrubyc/src/value.o mrubyc/src/vm.o
MRBCOBJ += sample_serial_echo_server.o
CROSS_CFLAGS += -std=c99 -I. -Imrubyc/src
CROSS_CFLAGS += -DMRBC_NO_TIMER

main.mot:	main.elf
	$(CROSS_OBJCOPY) main.elf -O srec -I elf32-rx-be-ns $@

main.elf:	$(OBJS) $(MRBCOBJ) sample_serial_echo_server.c
	$(CROSS_CC) $(CROSS_LIBS) $(CROSS_LDFLAGS) -o $@ *.o
	$(CROSS_SIZE) $@

.c.o:
	$(CROSS_CC) $(CROSS_CFLAGS) -c $<

start.o: start.S
	$(CROSS_CC) $(ASDEF) -c start.S

sample_serial_echo_server.c:
	../armbm-mruby/mruby/build/host/bin/mrbc -Bsample_serial_echo_server sample_serial_echo_server.rb

clean:
	rm -rf *.o *.elf *.mot  sample_serial_echo_server.c
