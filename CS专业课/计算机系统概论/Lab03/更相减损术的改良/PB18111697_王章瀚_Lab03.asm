		.ORIG	x3000

LOOP		NOT	R2, R1
		ADD	R2, R2, #1
		ADD	R3, R0, R2
		BRnz	NZ		;R0 > R1
P		ADD	R3, R3, R2	;减减看
		BRp	P		;是正数则减到非正
		ADD	R0, R1, R3	;更新R0为R1+R3
		BRnzp	LOOP
NZ		BRn	N		
		BRnzp	OK		;是0，结束
N		ADD	R3, R3, R0	;加加看
		BRn	N		;是负数则加到非负
		NOT	R3, R3
		ADD	R3, R3, #1
		ADD	R1, R0, R3	;更新R1为R0-R3
		BRnzp	LOOP

OK		HALT

		.END