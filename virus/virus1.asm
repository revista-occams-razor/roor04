section .text

	global _start
_start: mov rax, 1    ; SYS_write = 1
	mov rdi, 1        ; fd = 1 (stdout)
	lea rsi, [rel msg]
	mov rdx, LEN      ; tamaño de la cadena
	syscall  ; (SYS_write = rax(1), fd = rdi (1), buf = rsi (msg), count = rdx (LEN))  

	;;  Terminar Program
	mov rax, 0x3c  ; SYS_exit = 0x3c
	mov rdi, 0     ; status = 0
	syscall ; (SYS_exit = rax (0x3c), status = rdi (0))
	
	msg	db 'Que pasa lectores de Occams!!',0x0a
LEN:	 equ $-msg
