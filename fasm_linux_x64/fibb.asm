format ELF64 executable 3
segment readable executable
entry $
	mov rax, 1
	mov rdx, 1
	mov rcx, 5
.loop:
	xadd rax, rdx
	loop .loop
_end:
	mov rdi, rax
	mov rax, 60
	syscall
