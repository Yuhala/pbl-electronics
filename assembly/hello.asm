section .data
    hello db "Hello, World!", 0xA  ; Define string with newline (0xA)

section .text
    global _start                   ; Entry point

_start:
    mov rax, 1                      ; syscall: write
    mov rdi, 1                      ; file descriptor: stdout
    mov rsi, hello                  ; string address
    mov rdx, 14                     ; string length (including newline)
    syscall                         ; invoke system call

    mov rax, 60                     ; syscall: exit
    xor rdi, rdi                    ; exit status: 0
    syscall                         ; invoke system call
