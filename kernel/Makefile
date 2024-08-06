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
RM  :=  rm -rf
CCFLAGS	:=	-Wall -Wno-format -Wno-unused -Wno-unused-parameter -ffunction-sections \
		-ffreestanding -nostdinc -nostdlib -fno-builtin -fno-pie -static -I$(LIBPATH)
ASFLAGS	:=	-f bin
ifdef dbg
	CCFLAGS	+=	-g -D dbg
	ASFLAGS	+=	-g -D dbg
endif


DEFAULT: CLEAN BUILD
	# OVER

CLEAN:										# 清理
	-mkdir $(BDPATH)
	$(RM) $(BDPATH)/*
	$(RM) ./*.lock

BUILD: IPL FAT LOADER LLOADER DISK			# 構建

DISK:										# 寫入原始文件
#	dd if=/dev/zero of=$(BDPATH)/test.img bs=512 count=2880
	dd if=/dev/zero of=$(OUT) bs=512 count=32768
	dd if=$(BDPATH)/ipl.bin of=$(OUT) seek=0 bs=512 count=1 conv=notrunc
	dd if=$(BDPATH)/loader.asm.bin of=$(OUT) seek=1 bs=512 count=1 conv=notrunc
	dd if=$(BDPATH)/loader.c.bin of=$(OUT) seek=2 bs=512 count=14 conv=notrunc
	dd if=$(BDPATH)/SYMFS_fat.bin of=$(OUT) seek=16 bs=512 count=513 conv=notrunc
	dd if=$(BDPATH)/SYMFS_root.bin of=$(OUT) seek=529 bs=512 count=2 conv=notrunc
	dd if=$(BDPATH)/lloader.c.bin of=$(OUT) seek=531 bs=512 count=1 conv=notrunc
FAT: SYMFS_fat.asm SYMFS_root.asm			# 文件系統構建
	$(AS) SYMFS_fat.asm -o $(BDPATH)/SYMFS_fat.bin $(ASFLAGS)
	$(AS) SYMFS_root.asm -o $(BDPATH)/SYMFS_root.bin $(ASFLAGS)
IPL: ipl.asm								# IPL編譯
	$(AS) ipl.asm -o $(BDPATH)/ipl.bin $(ASFLAGS)
LOADER: loader.asm loader.c					# 加載程序編譯
	$(AS) loader.asm -o $(BDPATH)/loader.asm.bin $(ASFLAGS)
	$(CC) -c loader.c -o $(BDPATH)/loader.c.obj $(CCFLAGS) -I./ -m32
	$(AS) ./lib/loader/main.asm -o $(BDPATH)/lloader.asm.obj -f elf32
	$(LD) -m elf_i386 --oformat binary -o $(BDPATH)/loader.c.bin -T ./loader.lds \
		$(BDPATH)/loader.c.obj $(BDPATH)/lloader.asm.obj
LLOADER: lloader.c 							# 加載程序編譯
	$(CC) -c lloader.c -o $(BDPATH)/lloader.c.obj $(CCFLAGS) -I./ -m64
	$(LD) -m elf_x86_64 --oformat binary -o $(BDPATH)/lloader.c.bin -T ./loader.lds \
		$(BDPATH)/lloader.c.obj
