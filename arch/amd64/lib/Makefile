OBJECT	:= ctype.o string.o stdio.s.o string.s.o math.s.o stdio.s.o
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
