<<<<<<< HEAD
OBJECT	:= ctype.o string.o string.s.o math.o
KOBJECT	:= asm.s.o
=======
OBJECT	:= ctype.o string.o stdio.s.o string.s.o math.s.o stdio.s.o
KOBJECT	:= jump.s.o
>>>>>>> 0e6d8eadb2c2146548cad8704be56f3e4b9776a7

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
