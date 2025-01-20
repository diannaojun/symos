OBJECT	:= ctype.o string.o string.s.o math.o
KOBJECT	:= jump.s.o

archive: $(OBJECT) $(KOBJECT)
	$(AR) rcS libc.a $(OBJECT)
	$(AR) rcS libkc.a $(KOBJECT)

clean:
	- rm *.a
	- rm *.o

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.s.o: %.asm
	$(AS) -f elf64 $< -o $@
