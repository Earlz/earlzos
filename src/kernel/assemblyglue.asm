[BITS 64]
[SECTION .text]

global gdt_flush     ; Allows the C code to link to this
extern gp            ; Says that '_gp' is in another file
gdt_flush:
    lgdt [rel gp]        ; Load the GDT with our '_gp' which is a special pointer
    mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss,ax
    ;push 8 ;the segment for CS
    ;mov rax, flush2
    ;push rax
    ;retf
flush2:
    ret


;global idt_load
;extern idtp
;idt_load:
;    lidt [idtp]
;ret
