/* Global data section starts */
.data

N:
    .byte  8  

sum: 
    .long                 # 4 bytes

/* Code section starts */

.text
.global main
main:
    movl  $0, %eax        
    movl  $1, %ecx        # fib(n) <-> %ecx
    movl  $1, %edx            
    mov   N@GOTPCREL(%rip), %rbx        
    movzbl  (%rbx), %ebx    # N <-> %ebx
.Lback:
    cmpl  %edx, %ebx
    je .Lloopexit
    movl  %ecx, %esi        
    addl %eax, %ecx         
    movl  %esi, %eax         
    inc   %edx 
    jmp .Lback
.Lloopexit:
    ret
