AS		:=	nasm
CC		:=	gcc
PRJ		:=	$(CURDIR)

build: clean
	$(MAKE) -C ./arch build AS=$(AS) CC=$(CC) PRJ=$(PRJ) AR=$(AR)

debug: clean
	$(MAKE) -C ./arch debug AS=$(AS) CC=$(CC) PRJ=$(PRJ) AR=$(AR)

run: debug
	- bochsdbg

clean: *
ifeq ($(wildcard $(PRJ)/kernel), )
	- mkdir $(PRJ)/kernel
else
	- rm $(PRJ)/kernel/*
	$(MAKE) -C ./arch clean AS=$(AS) CC=$(CC) PRJ=$(PRJ) AR=$(AR)
endif
