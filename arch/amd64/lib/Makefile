OBJECT	:= ctype.o string.o stdio.s.o string.s.o math.s.o stdio.s.o

archive: $(OBJECT)
	$(AR) rcS libc.a $^

clean:
	- rm *.a
	- rm *.o

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.s.o: %.asm
	$(AS) -f elf64 $< -o $@
