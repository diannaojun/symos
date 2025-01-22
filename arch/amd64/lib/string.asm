bits 64

section .text
global strcpy, strcat, strcmp
global strncpy, strncat, strncmp
global strlen

strcpy:
    cld
    push rdi
    .loop:
	    lodsb
	    stosb
	    test al, al
	    jnz .loop
    pop rax
    ret
strncpy:
    cld
    push rdi
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
        pop rax
        ret
strcat:
    cld
    push rdi
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
    pop rax
    ret
strncat:
    cld
    push rdi
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
        xor al, al
        stosb
        pop rax
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
    .reta:
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
    .ret:
        xor eax, eax
        ret
    .retn:
        mov eax, 1
        ja .reta
        neg eax
    .reta:
        ret
strlen:
    cld
    xor al, al
    xor rcx, rcx
    dec rcx
    repnz scasb
    xor rax, rax
    sub rax, rcx
    ret
