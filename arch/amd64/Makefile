TEMP	:= $(CURDIR)/build
CFLAGS	:= -I$(CURDIR)/include -nostdlib -nostdinc -static -Wall -fno-builtin

build: clean boot

debug: build
	dd if=/dev/zero of=$(PRJ)/kernel/kernel.img seek=0 bs=512 count=2880
	dd if=$(TEMP)/boot.bin of=$(PRJ)/kernel/kernel.img seek=0 bs=512 count=2880 conv=notrunc

clean:
	$(MAKE) -C ./lib clean
ifeq ($(wildcard $(TEMP)), )
	- mkdir $(TEMP)
else
	- rm $(TEMP)/*
endif

boot: archive bin
	dd if=$(TEMP)/mbr.bin of=$(TEMP)/boot.bin seek=0 bs=512 count=1 conv=notrunc
	dd if=$(TEMP)/sdmp.bin of=$(TEMP)/boot.bin seek=1 bs=512 count=63 conv=notrunc
	dd if=$(TEMP)/setup.bin of=$(TEMP)/boot.bin seek=64 bs=512 count=4 conv=notrunc

bin: mbr.bin setup.bin sdmp.bin

setup.bin: setup.asm
	$(AS) setup.asm -o $(TEMP)/setup.bin -f bin -l $(TEMP)/setup.lst

mbr.bin: mbr.asm
	$(AS) mbr.asm -o $(TEMP)/mbr.bin -f bin -l $(TEMP)/mbr.lst

sdmp.bin: sdmp.asm
	$(AS) sdmp.asm -o $(TEMP)/sdmp.bin -f bin -l $(TEMP)/sdmp.lst

archive:
	$(MAKE) -C ./lib archive AS=$(AS) CC=$(CC) AR=$(AR)\
		PRJ=$(PRJ) TEMP=$(TEMP) "CFLAGS=$(CFLAGS)"
