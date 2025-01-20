bits 64

section .text
global strcpy, strcat, strcmp
global strncpy, strncat, strncmp

strcpy:
    cld
    .loop:
	    lodsb
	    stosb
	    test al, al
	    jnz .loop
    xor eax, eax
    ret
strncpy:
    cld
    xchg rcx, rdx
    .loop:
	    dec rcx
        js .ret
        lodsb
	    stosb
	    test al, al
	    jnz .loop
        rep stosb
    .ret:
        xor eax, eax
        ret
strcat:
    cld
    xor al, al
    xor rcx, rcx
    dec rcx
    repnz scasb
    dec rdi
    .loop:
	    lodsb
        stosb
	    test al, al
	    jnz .loop
    xor eax, eax
    ret
strncat:
    cld
    xor al, al
    xchg rcx, rdx
    repnz scasb
    dec rdi
    .loop:
	    dec rcx
        js .ret
	    lodsb
        stosb
	    test al, al
	    jnz .loop
    .ret:
        xor eax, eax
        stosb
        ret
strcmp:
    cld
    .loop:
        lodsb
        scasb
        jne .retn
        test al, al
        jnz .loop
        xor eax, eax
        ret
    .retn:
        mov eax, 1
        ja .reta
        neg eax
    .reta
        ret
strncmp:
    cld
    xchg rcx, rdx
    .loop:
        dec rcx
        js .ret
        lodsb
        scasb
        jne .retn
        test al, al
        jnz .loop
    .ret
        xor eax, eax
        ret
    .retn:
        mov eax, 1
        ja .reta
        neg eax
    .reta
        ret
