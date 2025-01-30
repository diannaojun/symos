AS		:=	nasm
CC		:=	gcc
LD		:=	ld
OBJCOPY :=	objcopy
AR 		:=	ar

build: font amd64_build

debug:
	$(MAKE) -C ./amd64 debug AS=$(AS) PRJ=$(PRJ) CC=$(CC) AR=$(AR)

amd64_build:
	$(MAKE) -C ./amd64 build AS=$(AS) PRJ=$(PRJ) CC=$(CC) AR=$(AR)

clean:
	$(MAKE) -C ./amd64 clean PRJ=$(PRJ)
	- rm $(PRJ)/extra/*.fnt

font:
	$(AS) $(PRJ)/extra/kernelfont.asm -o $(PRJ)/extra/kernelfont.fnt -f bin
