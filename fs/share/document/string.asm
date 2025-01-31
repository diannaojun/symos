dq (lang_table.end - lang_table) >> 4

lang_table:
    db "EN", 0, 0
    db "US", 0, 0
    dq en_us
    db "KIKI"
    db "HAN", 0
    dq ki_rk
    .end:

en_us:
    dq (.table.end - .table) >> 3
    .table:
        dq .string.language
        dq .string.country
        .table.end:
    .string.language    db "English", 0
    .string.country     db "United States", 0
ki_rk:
    dq (.table.end - .table) >> 3
    .table:
        dq .string.language
        dq .string.country
        dq .string.error0001
        dq .string.error0002
        dq .string.error0003
       .table.end:
    .string.language    db "Kiki", 0
    .string.country     db "Hanpang", 0
    .string.error0001   db "[MBR::0001] pa lio xizangto 13 Cendot.", 0
    .string.error0002   db "[MBR::0002] pa lio SDM Pankue.", 0
    .string.error0003   db "[MBR::0003] linto-Makue az SDM Pankue e ylom.", 0
