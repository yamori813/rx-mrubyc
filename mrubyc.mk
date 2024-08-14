MRBCOBJ = alloc.o c_array.o c_hash.o c_math.o c_numeric.o c_object.o c_range.o c_string.o class.o console.o error.o global.o keyvalue.o load.o mrblib.o rrt0.o symbol.o value.o vm.o
CROSS_CFLAGS += -std=c99 -I. -I../mrubyc/src
#CROSS_CFLAGS += -DMRBC_NO_TIMER
CROSS_CFLAGS += -DMRBC_USE_STRING=1

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
