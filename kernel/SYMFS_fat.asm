; Symbol DT
; Sym SFS Sys
; DiannaoJun
; 2024-08-09

TIMES 16 DQ 0xfffffffffffffff0						; MBR(IPL) L16 L32保留區
TIMES (16*1024*1024/512*8/512) DQ 0xfffffffffffffff0		; FAT(16MB)
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
DQ 0xfffffffffffffff0								; L64
