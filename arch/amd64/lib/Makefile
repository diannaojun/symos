OBJECT	:= ctype.o string.o

archive: $(OBJECT)
	$(AR) -rcS libc.a $^

clean:
	- rm *.a
	- rm *.o

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAG)

%.o: %.asm
	$(AS) -f elf64 $< -o $@
