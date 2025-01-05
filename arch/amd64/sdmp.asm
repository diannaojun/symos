%include "config.inc"

db "SDM PART"               ; SDM头符号
dw 0x0002                   ; 版本 0.2
dw 0x0040                   ; 头长度 64 扇区
dd 0x00000003               ; 分区总数 3
times 512-($-$$) db 0

align 64
db "        "               ; 分区名称
dw 0xffff                   ; 分区类型
db 0xff, 0x00               ; 分区状态
dd 0x00000000               ; 分区标识
dq 0x0000000000000000       ; 分区起始扇区
dq 0x0000000000000040       ; 分区扇区长度

align 64
db "SYM KNL "
dw 0x005a
db 0x5a, 0x00
dd 0x3683445a
dq 0x0000000000000040
dq 0x0000000000000040

times (63*512)-($-$$) db 0

; 分区类型
;   0000 未知
;   0001 FAT12
;   0002 XENIX /
;   0003 XENIX /usr/
;   0004 FAT16 (小于32MB)
;   0005 DOS Extended
;   0006 FAT16
;   0007 HPFS/NTFS/ExFAT
;   0008 AIX
;   0009 AIX Boot
;   000a OS/2 Boot
;   000b Windows 95 FAT32
;   000c Windows 95 FAT32 LBA
;   000e Windows 95 FAT16
;   000f Windows 95(DOS) Extended LBA (大于 8GB)
;   0010 OPUS
;   0011 Hidden FAT12
;   0012 EISA隐藏分区 (Compaq Diagonstics使用)
;   0014 Hidden FAT16 (小于32MB) or Maverick OS Omega FS
;   0016 Hidden FAT16
;   0017 Hidden HPFS/NTFS
;   0018 AST Windows Swap
;   001b Hidden FAT32
;   001c Hidden FAT32 LBA
;   001e Hidden LBA VFAT
;   0024 NEC MS-DOS 3.x
;   0027 Mcrosoft recovery partition
;   0035 OS/2 JFS
;   0038 THEOS V3 2GB
;   0039 THEOS V4 spanned
;   003a THEOS V4 4GB
;   003b THEOS V4 extended
;   003c PartitionMagic recovery
;   003d Novell Netware(Hidden)
;   0040 VENIX 286
;   0041 PPC PreP Boot or Linux/MINIX (sharing with DRDOS)
;   0042 SFS or RAID
;   0043 Linux native (sharing with DRDOS)
;   0045 Boot-US
;   004c Oberon
;   004d QNX 4.2 Primary
;   004e QNX 4.2 Secondary
;   004f QNX 4.2 Tertiary
;   0050 DM (Disk Danager)
;   0051 Novell (or DM6 Aux1)
;   0052 CP/M or Microport SysV/AT
;   0053 DM6 Aux3 (Disk Danager)
;   0054 DM6 Aux3 (Disk Danager)
;   0055 EZ-Drive (Disk Manager)
;   0056 Golden Bow (Disk Manager)
;   0057 DrivePro
;   005a Symbol FS
;   005b Symbol Disk Manager Part
;   005c Priam Edisk (DiskManager)
;   0061 SpeedStor
;   0063 Unix, System V/386, GNU HURD or Mach
;   0064 Novell Netware/286 2.xx
;   0065 Novell Netware/386 3.xx
;   0066 Novell Netware/286 2.xx
;   0067 Novell Netware/286 2.xx
;   0068 Novell Netware/286 2.xx
;   0069 Novell Netware/286 2.xx
;   0070 DiskSecure Multi-Boot
;   0074 Scramdisk
;   0075 PC/IX
;   0077 QNX 4.x
;   0078 QNX 4.x 2nd
;   0079 QNX 4.x 3rd
;   0080 Minix until 1.4a
;   0081 Early Linux, or Minix since 1.4b
;   0082 Linux swap
;   0083 Linux
;   0084 OS/2 Hidden C:
;   0085 Linux Extended
;   0086 FAT16 Volume
;   0087 NTFS Volume
;   008b FAT32 Volume
;   008c FAT32 LBA Volume
;   0093 Amoeda
;   0094 Amoeda Bad Blocks Table
;   009f BSD/OS
;   00a0 Hibernation
;   00a1 Hibernation
;   00a0 IBM Thinkpad Hidden
;   00a5 FreeBSD/NetBSD/386BSD
;   00a6 OpenBSD
;   00a7 NextStep
;   00a9 NetBSD
;   00aa Olivetti FAT12
;   00ac IBM JFS
;   00b7 BSDI BSD/386
;   00b8 BSDI BSD/386 swap
;   00be Solaris Boot
;   00c0 DR-DOS/Novell DOS Secured
;   00c1 DRDOS/sec FAT12
;   00c4 DRDOS/sec FAT16
;   00c6 Corrupted FAT16
;   00c7 Corrupted NTFS
;   00d8 CP/M-86
;   00db CP/M, Concurrent DOS or CTOS
;   00df BootIt
;   00e1 DOS access FAT12
;   00e3 DOS R/0 or SpeedStor
;   00e4 SpeedStor FAT16
;   00eb BeOS FS
;   00ee Protected MBR
;   00ef EFI System Partition
;   00f1 SpeedStor
;   00f2 DOS 3.3+ 2nd
;   00f4 SpeedStor Large
;   00fb VMware VMFS
;   00fc VMware swap
;   00fd Linux RAID
;   00fe LAN STEP
;   00ff Bad Blocks Table
;   ff?? 保留
;   fffd MBR扇区
;   fffe GPT扇区
;   ffff 磁盘头

; 分区状态
;   00 空的
;   5a 可引导的
;   80 正常的
;   fd 坏的
;   fe 保留
;   ff 保护
