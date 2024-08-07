TIMES 16 DQ 0xfffffffffffffff0						; MBR(IPL) L16 L32保留區
TIMES 512 DQ 0xfffffffffffffff0		                ; FAT(16MB) ((16*1024*1024/512*8+511)/512)
DQ 0xffffffffffffffff								; ROOT
DQ 0xffffffffffffffff								; PATH_SYS
DQ (($-$$)/8)+1
DQ (($-$$)/8)+1
DQ (($-$$)/8)+1
DQ (($-$$)/8)+1
DQ (($-$$)/8)+1
DQ (($-$$)/8)+1
DQ (($-$$)/8)+1
DQ (($-$$)/8)+1
DQ (($-$$)/8)+1
DQ (($-$$)/8)+1
DQ (($-$$)/8)+1
DQ (($-$$)/8)+1
DQ (($-$$)/8)+1
DQ (($-$$)/8)+1
DQ (($-$$)/8)+1
DQ 0xffffffffffffffff								; L64
