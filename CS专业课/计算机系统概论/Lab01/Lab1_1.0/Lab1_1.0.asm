; R0	lastMax
; R1	grade
; R2	maxgrade
; R3	grade location
; R4	dest location
; R5	only for temp 
; R6	counter, 60->0
; R7	global counter, 60->0

		.ORIG		x3000		; start from x3000
		LD		R4, DEST	; load the address of the grads
		LD		R0, MAXGRADE	; initialize the R0 to MAXGRADE
		LD		R7, NUM		; initialize the R7 to NUM of students
		LDI		R5, As		
		AND		R5, R5, #0	; let R5 <- #0
		STI		R5, As		; initialize the As to 0
		STI		R5, Bs		; initialize the Bs to 0
		STI		R5, Cs		; initialize the Cs to 0
		STI		R5, Ds		; initialize the Ds to 0

storeLoop	LD		R3, GRADE	; load the address of the grads
		AND		R2, R2, #0	; initialize the R2 to #0
		LD		R6, NUM		; initialize the counter(R6) into 60

findMaxLoop	LDR		R1, R3, #0	; load the current grade
		NOT		R5, R2
		ADD		R5, R5, #1
		ADD		R5, R5, R1	; R5 <- (R1-R3)
		BRn		nothing		; R1 less than maxgrade(R3)?
		NOT		R5, R0
		ADD		R5, R5, #1
		ADD		R5, R5, R1	; R5 <- (R1-R0)
		BRzp		nothing		; R1 less than lastMax(R0)? if not, goto nothing.
		AND		R2, R2, #0
		ADD		R2, R1, #0	; set the maxGrade(R2) as the current grade(R1) if not, goto nothing.
nothing		ADD		R3, R3, #1
		ADD		R6, R6, #-1
		BRp		findMaxLoop	; has counter counted to 0? if not, goto findMaxLoop.
		AND		R0, R0, #0
		ADD		R0, R2, #0	; R0 <- R2, lastMax <- maxgrade
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
		ADD		R5, R7, R5	; R5 <- (R7-A_GRADE) 
		BRnz		NOTA		; else if(R7 <= A_RANK) goto NOTA
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
		ADD		R5, R7, R5	; R5 <- (R7-B_RANK) 
		BRnz		NOTB		; else if(R7 <= B_RANK) goto NOTB
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
		ADD		R7, R7, #-1	; globalCounter--
		BRp		storeLoop	; has globalCounter counted to 0? if not, goto storeLoop.
		HALT
		

A_GRADE		.FILL		85		; the least grade requirement for A
B_GRADE		.FILL		75		; the least grade requirement for B
D_GRADE		.FILL		59		; the grade requirement for D
A_RANK		.FILL		42		; the rank requirement for A. NUM-NUM*30%=42. If global counter(R7) > A_RANK, then As++.
B_RANK		.FILL		30		; the rank requirement for B. NUM-NUM*50%=30. If global counter(R7) > B_RANK, then Bs++.

NUM		.FILL		#60		; the number of students.
MAXGRADE	.FILL		#105		; the max grade can be.
GRADE		.FILL		x3200		; the start address of grades
DEST		.FILL		x4000		; the start address of destination.
As		.FILL		x4100		; the address of number of As.
Bs		.FILL		x4101		; the address of number of Bs.
Cs		.FILL		x4102		; the address of number of Cs.
Ds		.FILL		x4103		; the address of number of Ds.
		.END