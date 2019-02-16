section .text

	global _start
        push rdi
        push rsi
        push rdx
_start: mov rax, 1    ; SYS_write = 1
	mov rdi, 1        ; fd = 1 (stdout)
	lea rsi, [rel msg]
	mov rdx, LEN      ; tamaño de la cadena
	syscall  ; (SYS_write = rax(1), fd = rdi (1), buf = rsi (msg), count = rdx (LEN))  
	pop rdx
        pop rsi
        pop rdi
	mov rax, 0xaabbccdd
	jmp rax
	msg	db 'Que pasa lectores de Occams!!',0x0a
LEN:	 equ $-msg
