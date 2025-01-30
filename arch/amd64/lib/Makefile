OBJECT	:= ctype.o string.o stdio.o string.s.o math.o
KOBJECT	:= kernel/asm.s.o\
		kernel/idt.s.o kernel/idt.o\
		kernel/mm.o

archive: $(OBJECT) $(KOBJECT)
	$(AR) -rcs libc.a $(OBJECT)
	$(AR) -rcs libkc.a $(OBJECT) $(KOBJECT)
	- rm */*.o
	- rm *.o

clean:
	- rm *.a
	- rm *.o
	- rm */*.o

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.s.o: %.asm
	$(AS) -f elf64 $< -o $@
