AS		:=	nasm
CC		:=	gcc
LD		:=	ld
OBJCOPY :=	objcopy
AR 		:=	ar

build: font amd64_build

debug: font
	$(MAKE) -C ./amd64 debug AS=$(AS) PRJ=$(PRJ) CC=$(CC) AR=$(AR)

amd64_build:
	$(MAKE) -C ./amd64 build AS=$(AS) PRJ=$(PRJ) CC=$(CC) AR=$(AR)

clean:
	$(MAKE) -C ./amd64 clean PRJ=$(PRJ)
	- rm $(PRJ)/fs/kernel/*.fnt

font:
	$(AS) $(PRJ)/fs/kernel/kernel.fnt.asm -o $(PRJ)/fs/kernel/kernel.fnt -f bin
