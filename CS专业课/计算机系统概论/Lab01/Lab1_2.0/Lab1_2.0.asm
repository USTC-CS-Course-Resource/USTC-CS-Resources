; R1	grade
; R2	maxgrade
; R3	grade location
; R4	dest location
; R5	only for temp 
; R6	lastMax

		.ORIG		x3000		; start from x3000
		LD		R4, DEST	; load the address of the grads
		LD		R6, MAXGRADE	; initialize the R6 to MAXGRADE
		LDI		R5, As		
		AND		R5, R5, #0	; R5 <- #0
		STI		R5, As		; initialize the As to 0
		STI		R5, Bs		; initialize the Bs to 0
		STI		R5, Cs		; initialize the Cs to 0
		STI		R5, Ds		; initialize the Ds to 0

storeLoop	LD		R3, GRADE	; load the address of the grads
		AND		R2, R2, #0	; initialize the R2 to #0

findMaxLoop	LDR		R1, R3, #0	; load the current grade
		NOT		R5, R2
		ADD		R5, R5, #1
		ADD		R5, R5, R1	; R5 <- (R1-R3)
		BRn		nothing		; R1 less than maxgrade(R3)?
		NOT		R5, R6
		ADD		R5, R5, #1
		ADD		R5, R5, R1	; R5 <- (R1-R6)
		BRzp		nothing		; R1 less than lastMax(R6)? if not, goto nothing.
		AND		R2, R2, #0
		ADD		R2, R1, #0	; set the maxGrade(R2) as the current grade(R1) if not, goto nothing.
nothing		ADD		R3, R3, #1
		LD		R5, GRADE_END	;
		NOT		R5, R5		;
		ADD		R5, R5, #1	;
		ADD		R5, R5, R3	;
		BRnz		findMaxLoop	; has R3 reached GRADE_END? If not, goto findMaxLoop.
		AND		R6, R6, #0
		ADD		R6, R2, #0	; R6 <- R2, lastMax <- maxgrade
		STR		R2, R4, #0	; have got the max, store it

; Find the A/B/C/D for this maxgrade.
; try A
		LD		R5, A_GRADE	
		NOT		R5, R5
		ADD		R5, R5, #1
		ADD		R5, R2, R5	; R5 <- (R2-A_GRADE) 
		BRn		NOTA		; if(R2 < A_GRADE) goto NOTA
		LD		R5, A_RANK
		NOT		R5, R5
		ADD		R5, R5, #1
		ADD		R5, R3, R5	; R5 <- (R3-A_RANK) 
		BRp		NOTA		; else if(R5 > 0) goto NOTA
		LDI		R5, As		; load the address of statistics information.
		ADD		R5, R5, #1	; As++
		STI		R5, As
		BRnzp		LOOP_PRE	
; else try B
NOTA		LD		R5, B_GRADE	
		NOT		R5, R5
		ADD		R5, R5, #1
		ADD		R5, R2, R5	; R5 <- (R2-B_GRADE) 
		BRn		NOTB		; if(R2 < B_GRADE) goto NOTB
		LD		R5, B_RANK
		NOT		R5, R5
		ADD		R5, R5, #1
		ADD		R5, R3, R5	; R5 <- (R3-B_RANK) 
		BRp		NOTA		; else if(R5 > 0) goto NOTB
		LDI		R5, Bs		; load the address of statistics information.
		ADD		R5, R5, #1	; Bs++
		STI		R5, Bs		; store the new Bs
		BRnzp		LOOP_PRE	
; else try D
NOTB		LD		R5, D_GRADE	
		NOT		R5, R5
		ADD		R5, R5, #1
		ADD		R5, R2, R5	; R5 <- (R2-D_GRADE) 
		BRp		NOTD		; if(R2 < D_GRADE) goto NOTD
		LDI		R5, Ds		; load the address of statistics information.
		ADD		R5, R5, #1	; Ds++
		STI		R5, Ds		; store the new Ds
		BRnzp		LOOP_PRE	
; else, C
NOTD		LDI		R5, Cs		; load the address of statistics infsormation.
		ADD		R5, R5, #1	; Cs++
		STI		R5, Cs		; store the new Cs

LOOP_PRE	ADD		R4, R4, #1	; update R4 to the new dest location
		LD		R5, DEST_END
		NOT		R5, R5
		ADD		R5, R5, #1
		ADD		R5, R5, R4
		BRnz		storeLoop	; has R4 reached DEST_END?
		HALT
		

A_GRADE		.FILL		85		; the least grade requirement for A
B_GRADE		.FILL		75		; the least grade requirement for B
D_GRADE		.FILL		59		; the grade requirement for D
A_RANK		.FILL		x4011		; the rank requirement for A. Who gets A must be at or before A_RANK.
B_RANK		.FILL		x401C		; the rank requirement for B. Who gets B must be at or before B_RANK.

NUM		.FILL		#60		; the number of students.
MAXGRADE	.FILL		#105		; the max grade can be.
GRADE		.FILL		x3200		; the start address of grades
GRADE_END	.FILL		x323B		; the end address of grades
DEST		.FILL		x4000		; the start address of destination.
DEST_END	.FILL		x403B		; the end address of destination.
As		.FILL		x4100		; the address of number of As.
Bs		.FILL		x4101		; the address of number of Bs.
Cs		.FILL		x4102		; the address of number of Cs.
Ds		.FILL		x4103		; the address of number of Ds.
		.END