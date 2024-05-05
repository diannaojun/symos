# Symbol DT
# SymOS
# DiannaoJun
# 2024-03-31

BDPATH	:=	./building
GCCPATH	:=
LIBPATH	:=	../lib/include
OUT	:=	kernel.img
AS	:=	nasm
CC	:=	$(GCCPATH)gcc
LD	:=	$(GCCPATH)ld
CCFLAGS	:=	-Wall -Wno-format -Wno-unused -Wno-unused-parameter -ffunction-sections \
		-ffreestanding -nostdinc -nostdlib -fno-builtin -fno-pie -static -I$(LIBPATH)
ASFLAGS	:=	-f bin
ifdef dbg
	CCFLAGS	+=	-g -D dbg
	ASFLAGS	+=	-g -D dbg
endif


DEFAULT: CLEAN BUILD
	# OVER

CLEAN:
	-mkdir $(BDPATH)
	rm -rf $(BDPATH)/*
	rm -rf ./*.lock

BUILD: IPL LOADER DISK
	# BUUILDING

DISK:
	dd if=/dev/zero of=$(BDPATH)/test.img bs=512 count=2880
	dd if=/dev/zero of=$(OUT) bs=512 count=32768
	dd if=$(BDPATH)/ipl.bin of=$(OUT) seek=0 bs=512 count=1 conv=notrunc
	dd if=$(BDPATH)/loader.asm.bin of=$(OUT) seek=1 bs=512 count=1 conv=notrunc
	dd if=$(BDPATH)/loader.c.bin of=$(OUT) seek=2 bs=512 count=14 conv=notrunc
# 	dd if=$(BDPATH)/lloader.c.bin of=$(OUT) seek=14 bs=512 count=1 conv=notrunc

IPL: ipl.asm
	$(AS) ipl.asm -o $(BDPATH)/ipl.bin $(ASFLAGS)
LOADER: loader.asm loader.c
	$(AS) loader.asm -o $(BDPATH)/loader.asm.bin $(ASFLAGS)
	$(CC) -c loader.c -o $(BDPATH)/loader.c.obj $(CCFLAGS) -I./ -m32
	$(AS) ./lib/loader/main.asm -o $(BDPATH)/loader.loader.asm.obj -f elf32
	$(LD) -m elf_i386 --oformat binary -o $(BDPATH)/loader.c.bin -T ./loader.lds \
		$(BDPATH)/loader.c.obj $(BDPATH)/loader.loader.asm.obj
LLOADER: lloader.c 
	$(CC) -c lloader.c -o $(BDPATH)/lloader.c.obj $(CCFLAGS) -I./ -m64
	$(LD) -m elf_x86_64 --oformat binary -o $(BDPATH)/lloader.c.bin -T ./loader.lds \
		$(BDPATH)/lloader.c.obj