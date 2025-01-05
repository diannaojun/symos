default: build

build: boot
	echo $(db)

clean:
	- rm $(TEMP)/*

boot: mbr.bin setup.bin sdmp.bin
	dd if=$(TEMP)/mbr.bin of=$(TEMP)/boot.bin seek=0 bs=512 count=1 conv=notrunc
	dd if=$(TEMP)/sdmp.bin of=$(TEMP)/boot.bin seek=1 bs=512 count=63 conv=notrunc
	dd if=$(TEMP)/setup.bin of=$(TEMP)/boot.bin seek=64 bs=512 count=4 conv=notrunc

setup.bin: setup.asm
	$(AS) setup.asm -o $(TEMP)/setup.bin -f bin -l $(TEMP)/setup.lst

mbr.bin: mbr.asm
	$(AS) mbr.asm -o $(TEMP)/mbr.bin -f bin -l $(TEMP)/mbr.lst

sdmp.bin: sdmp.asm
	$(AS) sdmp.asm -o $(TEMP)/sdmp.bin -f bin -l $(TEMP)/sdmp.lst

