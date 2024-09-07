; Symbol DT
; Sym SFS Sys
; DiannaoJun
; 2024-08-09

; SELF:
	DB ".              "
	DB 00010000b
	DQ 0x210
	DQ 0x200
; FATH:
	DB "..             "
	DB 00010000b
	DQ 0x210
	DQ 0x200
; SYS_PATH:
	DB "SYS            "
	DB 00010000b
	DQ 0x211
	DQ 0x200
TIMES (512*1)-($-$$) DB 0x00

; SELF:
	DB ".              "
	DB 00010000b
	DQ 0x211
	DQ 0x200
; FATH:
	DB "..             "
	DB 00010000b
	DQ 0x210
	DQ 0x200
; IPL:
	DB "IPL.SYS        "
	DB 00000111b
	DQ 0x00
	DQ 0x200
; L16:
	DB "L16.SYS        "
	DB 00000111b
	DQ 0x01
	DQ 0x200
; L32:
	DB "L32.SYS        "
	DB 00000111b
	DQ 0x02
	DQ 0x200*14
; L64:
	DB "L64.SYS        "
	DB 00000111b
	DQ 0x212
	DQ 0x200
TIMES (512*2)-($-$$) DB 0x00
