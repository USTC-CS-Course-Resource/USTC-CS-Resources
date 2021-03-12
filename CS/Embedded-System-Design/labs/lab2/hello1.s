.data
    msg:    .asciz  "hello, world\n"
    len = .-msg
.text
        .align  2
.global _start
_start:
    mov r0, #1
    ldr r1, =msg
    ldr r2, =len
    mov r7, #4
    swi #0
    mov r0, #0
    mov r7, #1
    swi #0
.end
