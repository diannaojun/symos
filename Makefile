AS		:=	nasm
PRJ		:=	$(CURDIR)
TEMP	:=	$(PRJ)/build
FLATS   :=  1024

default: build

build: clean
	dd if=/dev/zero of=$(TEMP)/boot.bin bs=512 count=$(FLATS)
	$(MAKE) -C ./arch build_all AS=$(AS) PRJ=$(PRJ) TEMP=$(TEMP)

debug: build
	dd if=$(TEMP)/boot.bin of=$(PRJ)/kernel/kernel.img
	gcc $(PRJ)/tool/vmdk.c -o $(TEMP)/vmdk.exe
	$(TEMP)/vmdk.exe $(FLATS) $(PRJ)/kernel/kernel kernel

clean:
ifeq ($(wildcard $(TEMP)), )
	- mkdir $(TEMP)
	- mkdir $(PRJ)/kernel
else
	$(MAKE) -C ./arch clean_all AS=$(AS) PRJ=$(PRJ) TEMP=$(TEMP)
	- rm $(PRJ)/kernel/*
endif
