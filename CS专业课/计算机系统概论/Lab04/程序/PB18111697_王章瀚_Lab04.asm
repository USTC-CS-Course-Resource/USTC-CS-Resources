		.ORIG	x3000
		AND	R0, R0, #0
		AND	R1, R1, #0
		AND	R2, R2, #0
		AND	R3, R3, #0
		AND	R4, R4, #0
		AND	R5, R5, #0
		AND	R6, R6, #0
		AND	R7, R7, #0
		LD	R6, func_stack	;读取栈初始地址
		JSR	main
		LD	R0, main_ret	;读取返回值
		HALT

main		ST	R7, main_R7	;存好R7所保存的返回地址
		GETC
		LD	R1, c_n30
		ADD	R1, R0, R1	;计算初始n
		LD	R6, func_stack	;读取栈初始地址
		STR	R1, R6, #2	;把n存到R6+#1上
		AND	R1, R1, #0	;初始化R1为0
		STR	R1, R6, #3	;a处存为0
		STR	R1, R6, #4	;b处存为0
		STR	R1, R6, #5	;c处存为0
		STR	R1, R6, #6	;d处存为0
		STR	R1, R6, #7	;e处存为0
		STR	R1, R6, #8	;f处存为0
		JSR	func		;调用func
		LDR	R0, R6, #0	;读取返回值
		ADD	R6, R6, #-12	;R6回退
		ST	R0, main_ret	;返回值写到main函数返回值处
		LD	R7, main_R7
		RET
main_ret	.BLKW	1
main_R7		.BLKW	1

func		STR	R7, R6, #1	;存好R7所保存的返回地址
		GETC			;计算t开始
		LD	R1, c_n30	
		ADD	R0, R0, R1	;t-='0'
		LDR	R1, R6, #3	;从内存读取a
		ADD	R0, R0, R1	;加上a
		LDR	R1, R6, #4	;从内存读取b
		ADD	R0, R0, R1	;加上b
		LDR	R1, R6, #5	;从内存读取c
		ADD	R0, R0, R1	;加上c
		LDR	R1, R6, #6	;从内存读取d
		ADD	R0, R0, R1	;加上d
		LDR	R1, R6, #7	;从内存读取e
		ADD	R0, R0, R1	;加上e
		LDR	R1, R6, #8	;从内存读取f	
		ADD	R0, R0, R1	;加上f, 计算t结束
		STR	R0, R6, #9	;存放t

		LDR	R1, R6, #2	;读取n
		ADD	R2, R1, #-1	;计算n-1
		BRnz	ELSE		;若n-1<=0,跳转到ELSE

		ADD	R6, R6, #12	;将R6指向下一个栈空间，为下一次递归调用做准备
		LD	R3, stack_size	;读取栈空间总大小
		LD	R4, func_stack	;读取栈空间起始位置
		ADD	R3, R3, R4	;计算栈空间末尾位置
		NOT	R3, R3
		ADD	R3, R3, #1	;计算栈空间末位置的相反数
		ADD	R3, R3, R6	;R6-栈空间末位置
		BRz	stackoverflow	;栈溢出
		LDR	R1, R6, #-10	;从内存读取n
		ADD	R2, R1, #-1	;求n-1
		STR	R2, R6, #2	;存到R6+#2上
		LDR	R1, R6, #-9	;从内存读取a
		STR	R1, R6, #3	;存到R6+#3上
		LDR	R1, R6, #-8	;从内存读取b
		STR	R1, R6, #4	;存到R6+#4上
		LDR	R1, R6, #-7	;从内存读取c
		STR	R1, R6, #5	;存到R6+#5上
		LDR	R1, R6, #-6	;从内存读取d
		STR	R1, R6, #6	;存到R6+#6上
		LDR	R1, R6, #-5	;从内存读取e
		STR	R1, R6, #7	;存到R6+#7上
		LDR	R1, R6, #-4	;从内存读取f
		STR	R1, R6, #8	;存到R6+#8上
		JSR	func		;递归调用以求x
		LDR	R0, R6, #0	;读取递归调用求x得到的返回值
		STR	R0, R6, #-2	;存在当前栈的x空间位置上
		LDR	R1, R6, #-10	;从内存读取n
		ADD	R2, R1, #-2	;求n-2
		STR	R2, R6, #2	;存到R6+#2上
					;其余R1到R6上一次均已经存好，且未改变
		JSR	func		;递归调用以求y
		LDR	R0, R6, #0	;读取递归调用求y得到的返回值
		STR	R0, R6, #-1	;存在当前栈的y空间位置上
		
		ADD	R6, R6, #-12	;栈指针指回当前调用函数对应栈

		LDR	R0, R6, #9	;读取t到R0
		LDR	R1, R6, #10	;读取x到R1
		ADD	R0, R0, R1	;求t+x
		LDR	R1, R6, #11	;读取y到R1
		ADD	R0, R0, R1	;求t+x+y
		ADD	R0, R0, #-1	;求t+x+y-1
		STR	R0, R6, #0	;返回值存在R6+#0

		LDR	R7, R6, #1	;读取R7所保存的返回地址
		RET			;以上完成了n>1的情况
					;以下是n<=1的情况
ELSE		LDR	R0, R6, #9	;返回t,把t的值读入R0
		STR	R0, R6, #0	;返回值存在R6+#0
		LDR	R7, R6, #1	;读取R7所保存的返回地址
		RET			;n<=1，直接返回
stackoverflow	LEA	R0, sof_message
		PUTS
		HALT


sof_message	.STRINGZ "Stack OverFlow!"	
c_n30		.FILL	x-30		;'0'的ASCII的相反数
;stack_size	.FILL	#36		
stack_size	.FILL	x1C2C		;栈的大小+#12, x1C2C+#12=#7212
func_stack	.FILL	xD000		;为func函数的栈保留空间
					;func函数栈空间存储按照下述格式：
					;1. 每12个内存地址为一块
					;2. 每块顺序存放：
					;	x0	返回值
					;	x1	RET应返回到的R7
					;	x2	n
					;	x3	a
					;	x4	b
					;	x5	c
					;	x6	d
					;	x7	e
					;	x8	f
					;	x9	t
					;	xA	x
					;	xB	y

		.END