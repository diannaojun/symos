OBJECT	:= ctype.o string.o stdio.o string.s.o math.o
KOBJECT	:= asm.s.o

archive: $(OBJECT) $(KOBJECT)
	$(AR) rcs libc.a $(OBJECT)
	$(AR) rcs libkc.a $(KOBJECT)

clean:
	- rm *.a
	- rm *.o

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.s.o: %.asm
	$(AS) -f elf64 $< -o $@
