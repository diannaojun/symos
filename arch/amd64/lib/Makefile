OBJECT	:= string.o stddef.o

archive: $(OBJECT)
	$(AR) rcS libc.a $^

clean:
	- rm *.a
	- rm *.o

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAG)
