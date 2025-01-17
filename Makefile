AS		:=	nasm
PRJ		:=	$(CURDIR)
TEMP	:=	$(PRJ)/build
FLATS   :=  2880

default: build

build: clean
	dd if=/dev/zero of=$(TEMP)/boot.bin bs=512 count=$(FLATS)
	$(MAKE) -C ./lib build_all AS=$(AS) PRJ=$(PRJ) TEMP=$(TEMP)
	$(MAKE) -C ./arch build_all AS=$(AS) PRJ=$(PRJ) TEMP=$(TEMP)

debug:
	$(MAKE) build
	dd if=$(TEMP)/boot.bin of=$(PRJ)/kernel/kernel.img

run: debug
	- bochsdbg

clean:
ifeq ($(wildcard $(TEMP)), )
	- mkdir $(TEMP)
	- mkdir $(PRJ)/kernel
else
	$(MAKE) -C ./arch clean_all AS=$(AS) PRJ=$(PRJ) TEMP=$(TEMP)
	- rm $(PRJ)/kernel/*
endif
