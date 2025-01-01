default: build

build: boot

clean:
	- rm $(TEMP)/mbr.bin
	- rm $(TEMP)/setup.bin
	- rm $(TEMP)/boot.bin

boot: mbr.bin setup.bin
	dd if=$(TEMP)/mbr.bin of=$(TEMP)/boot.bin seek=0 bs=512 count=1 conv=notrunc
	dd if=$(TEMP)/setup.bin of=$(TEMP)/boot.bin seek=2 bs=512 count=3 conv=notrunc

setup.bin: setup.asm
	$(AS) setup.asm -o $(TEMP)/setup.bin -f bin

mbr.bin: mbr.asm
	$(AS) mbr.asm -o $(TEMP)/mbr.bin -f bin
