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

ifdef debug
	CCFLAGS	+=	-g -D debug
	ASFLAGS	+=	-g -D debug
endif


default: clean build
	# over

clean:										# 清理
	-mkdir $(BDPATH)
	$(RM) $(BDPATH)/*
	$(RM) *.lock
	$(RM) *.img

build: build_ipl build_fat build_loader build_lloader image			# 构建

image:										# 写入原始文件
	dd if=/dev/zero of=$(OUT) bs=512 count=32768
	dd if=$(BDPATH)/ipl.bin of=$(OUT) seek=0 bs=512 count=1 conv=notrunc
	dd if=$(BDPATH)/loader.asm.bin of=$(OUT) seek=1 bs=512 count=1 conv=notrunc
	dd if=$(BDPATH)/loader.c.bin of=$(OUT) seek=2 bs=512 count=14 conv=notrunc
	dd if=$(BDPATH)/SYMFS_fat.bin of=$(OUT) seek=16 bs=512 count=513 conv=notrunc
	dd if=$(BDPATH)/SYMFS_root.bin of=$(OUT) seek=528 bs=512 count=2 conv=notrunc
	dd if=$(BDPATH)/lloader.c.bin of=$(OUT) seek=530 bs=512 count=16 conv=notrunc

build_fat: SYMFS_fat.asm SYMFS_root.asm			# 文件系统构建
	$(AS) SYMFS_fat.asm -o $(BDPATH)/SYMFS_fat.bin $(ASFLAGS)
	$(AS) SYMFS_root.asm -o $(BDPATH)/SYMFS_root.bin $(ASFLAGS)

build_ipl: ipl.asm								# build_ipl 编译
	$(AS) ipl.asm -o $(BDPATH)/ipl.bin $(ASFLAGS)

build_loader: loader.asm loader.c					# 加载程序编译
	$(AS) loader.asm -o $(BDPATH)/loader.asm.bin $(ASFLAGS)
	$(CC) -c loader.c -o $(BDPATH)/loader.c.obj $(CCFLAGS) -I./ -m32
	$(AS) ./lib/loader/main.asm -o $(BDPATH)/loader.asm.obj -f elf32
	$(LD) -m elf_i386 --oformat binary -o $(BDPATH)/loader.c.bin -T ./loader.lds \
		$(BDPATH)/loader.c.obj $(BDPATH)/loader.asm.obj

build_lloader: lloader.c 							# 加载程序编译
	$(CC) -c lloader.c -o $(BDPATH)/lloader.c.obj $(CCFLAGS) -I./ -m64 -fpic
	$(AS) ./lib/lloader/lloader.asm -o $(BDPATH)/lloader.asm.obj -f elf64
	$(LD) -m elf_x86_64 --oformat binary -o $(BDPATH)/lloader.c.bin -T ./loader.lds \
		$(BDPATH)/lloader.c.obj $(BDPATH)/lloader.asm.obj
