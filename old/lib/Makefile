# Symbol DT
# SymOS
# DiannaoJun
# 2024-04-05

GCCPATH	:=
AS	:=	nasm
CC	:=	$(GCCPATH)gcc
CCFLAGS	:=	-Wall -Wno-format -Wno-unused -Wno-unused-parameter -ffunction-sections -ffreestanding -nostdinc -nostdlib -fno-builtin -fno-pie -static -m32 -I../lib/include
ASFLAGS	:=	-f elf

OBJ		:=	kernel

DEFAULT: $(OBJ)

kernel:
