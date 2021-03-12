	.global	strcmp
	.type	strcmp, %function
strcmp:
	str	fp, [sp, #-4]!	@ 把 fp 暂存一下
	add	fp, sp, #0		@ fp = sp
	sub	sp, sp, #20		@ 扩栈, sp -= 20
	str	r0, [fp, #-16]	@ 暂存参数 fp[-16] = str1
	str	r1, [fp, #-20]	@ 暂存参数 fp[-20] = str2
	mov	r3, #0			@ r3 = 0
	str	r3, [fp, #-8]	@ fp[-8] = r3
.cmp_loop:
	ldr	r3, [fp, #-8]	@ r3 = i
	ldr	r2, [fp, #-16]	@ r2 = str1
	add	r3, r2, r3		@ r3 = &(str1[i])
	ldrb	r2, [r3]	@ r2 = str1[i]
	ldr	r3, [fp, #-8]	@ r3 = i
	ldr	r1, [fp, #-20]	@ r1 = str2
	add	r3, r1, r3		@ r3 = &(str2[i])
	ldrb	r3, [r3]	@ r3 = str2[i]
	cmp	r2, r3			@ 比较 str1[i] 和 str2[i]
	bne	.cmp_done		@ 如果 str1[i] != str2[i] 就结束 while, 跳到 .L3
	cmp	r2, #0			@ 比较 str1[i] 和 0
	beq	.cmp_done		@ 如果 str1[i] == 0, 就继续循环
	ldr	r3, [fp, #-8]	@ 
	add	r3, r3, #1		@ i++
	str	r3, [fp, #-8]	@ 
	b	.cmp_loop
.cmp_done:
	sub	r0, r2, r3		@ 计算返回值 str1[i] - str2[i]
	add	sp, fp, #0		@ sp = fp
	@ sp needed
	ldr	fp, [sp], #4	@ 放回 fp
	bx	lr				@ 返回
	.size	strcmp, .-strcmp
	.align	2

@ strsort 函数
	.globl   strsort
	.p2align 2
	.type	strsort, %function
strsort:
	.fnstart
	push	{fp, lr}	@ 暂存 fp, lr(帧指针, 返回地址)
	add	fp, sp, #4		@ fp = sp + 4
	sub	sp, sp, #24		@ sp = sp - 24, 扩栈
	str	r0, [fp, #-24]	@ fp[-24] = strs
	str	r1, [fp, #-28]	@ fp[-28] = n
	mov	r3, #1			@ i = r3 = 1
	str	r3, [fp, #-12]	@ fp[-12] = i
	b	.outer_loop		@ 跳转到外层 for 循环
.outer_prepare:
	ldr	r3, [fp, #-12]	@ j = r3 = i
	sub	r3, r3, #1		@ j = r3 = i - 1
	str	r3, [fp, #-8]	@ fp[-8] = j
	ldr	r3, [fp, #-12]	@ r3 = i
	lsl	r3, r3, #2		@ r3 = i << 2
	ldr	r2, [fp, #-24]	@ r2 = strs
	add	r3, r2, r3		@ r3 = &(strs[i])
	ldr	r3, [r3]		@ r3 = strs[i]
	str	r3, [fp, #-16]	@ fp[-16] = strs[i]
	b	.inner_loop		@ 进入内层 while 循环
	
.pushback:
	ldr	r3, [fp, #-8]	@ r3 = j
	lsl	r3, r3, #2		@ r3 = j << 2
	ldr	r2, [fp, #-24]	@ r2 = strs
	add	r2, r2, r3		@ r2 = &(strs[j])
	ldr	r3, [fp, #-8]	@ r3 = j
	add	r3, r3, #1		@ r3 = j + 1
	lsl	r3, r3, #2		@ r3 = (j + 1) << 2
	ldr	r1, [fp, #-24]	@ r1 = strs
	add	r3, r1, r3		@ r3 = &(strs[j+1])
	ldr	r2, [r2]		@ r2 = strs[j]
	str	r2, [r3]		@ strs[j+1] = strs[j]
	ldr	r3, [fp, #-8]	@ r3 = j
	sub	r3, r3, #1		@ j--
	str	r3, [fp, #-8]	@ fp[-8] = j
.inner_loop:
	ldr	r3, [fp, #-8]	@ r3 = j
	cmp	r3, #0			@ 比较 j 和 0
	blt	.put_i			@ 若 j < 0, 内层循环结束, 跳转到 .L9
	lsl	r3, r3, #2		@ j << 2
	ldr	r2, [fp, #-24]	@ r2 = strs
	add	r3, r2, r3		@ r3 = &(strs[j])
	ldr	r3, [r3]		@ r3 = strs[j]
	ldr	r1, [fp, #-16]	@ r1 = strs[i]
	mov	r0, r3			@ r0 = strs[j]
	bl	strcmp			@ strcmp(strs[j], strs[i])
	cmp	r0, #0			@ 比较 strcmp(strs[j], strs[i]) 和 0
	bgt	.pushback		@ 如果 strs[j] > strs[i], 则需要让strs[j+1] = strs[j]
.put_i:					@ 否则就内存循环结束
	ldr	r3, [fp, #-8]	@ r3 = j
	add	r3, r3, #1		@ r3 = j + 1
	lsl	r3, r3, #2		@ r3 = (j+1) << 2
	ldr	r2, [fp, #-24]	@ r2 = strs
	add	r3, r2, r3		@ r2 = &(strs[j+1])
	ldr	r2, [fp, #-16]	@ r2 = strs[i]
	str	r2, [r3]		@ strs[j+1] = strs[i]
	ldr	r3, [fp, #-12]	@ r3 = i
	add	r3, r3, #1		@ i++
	str	r3, [fp, #-12]	@ fp[-12] = i

.outer_loop:
	ldr	r2, [fp, #-12]	@ r2 = i
	ldr	r3, [fp, #-28]	@ r3 = n 
	cmp	r2, r3			@ 比较 i 和 n
	blt	.outer_prepare	@ 若 i < n, 跳转到 .L11
	nop
	sub	sp, fp, #4		@ 恢复 sp
	@ sp needed
	pop	{fp, pc}		@ 恢复 fp, pc
	.size	strsort, .-strsort
	.align	2

	.fnend
