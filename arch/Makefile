AS		:=	nasm
CC		:=	gcc
LD		:=	ld
OBJCOPY :=	objcopy
AR 		:=	ar

build: amd64_build

debug:
	$(MAKE) -C ./amd64 debug AS=$(AS) PRJ=$(PRJ) CC=$(CC) AR=$(AR)

amd64_build:
	$(MAKE) -C ./amd64 build AS=$(AS) PRJ=$(PRJ) CC=$(CC) AR=$(AR)

clean:
	$(MAKE) -C ./amd64 clean PRJ=$(PRJ)
