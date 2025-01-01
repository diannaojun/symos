AS		:=	nasm
PRJ		:=	$(CURDIR)
TEMP	:=	$(PRJ)/build

default: build

build: clean
	$(MAKE) -C ./arch build_all AS=$(AS) PRJ=$(PRJ) TEMP=$(TEMP)
	dd if=$(TEMP)/boot.bin of=kernel/kernel.img

clean:
ifeq ($(wildcard $(TEMP)), )
	- mkdir $(TEMP)
else
	$(MAKE) -C ./arch clean_all AS=$(AS) PRJ=$(PRJ) TEMP=$(TEMP)
endif
