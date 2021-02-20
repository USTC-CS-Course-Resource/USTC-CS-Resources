		.ORIG		x3000		; start from x3000

;;;;; PART 1 ;;;;;
; make the destination memory into 0, from DEST to DEST_END
; R1	DEST
; R2	nDEST_END100
; R3	-1
		
		LD		R1, DEST
		LD		R2, nDEST_END100
		AND		R3, R3, #0
		ADD		R3, R3, #-1
SETn1_LOOP	STR		R3, R1, #0	; store 0 into the position
		ADD		R1, R1, #1	; R1 ++
		ADD		R5, R1, R2	
		BRnz		SETn1_LOOP	; check whether finished.

;;;;; PART 2 ;;;;;
; search all the grade and put them into the according memory
; R1	grade location
; R2	nGRADE_END
; R3	DEST_END100	
; R4	grade
; R5	only for temp

		LD		R1, GRADE	; load the grades' address
		LD		R2, nGRADE_END	; load the opposite number of grades' end address
		LD		R3, DEST_END100	; load DEST_END100

SEARCH_LOOP	LDR		R4, R1, #0	; load the grade to R4 by R1	
		NOT		R5, R4
		ADD		R5, R5, #1
		ADD		R5, R5, R3	; get the position the grade should be
		STR		R4, R5, #0	; store the grade into the position
		ADD		R1, R1, #1	; R1 ++
		ADD		R5, R1, R2	
		BRnz		SEARCH_LOOP	; check whether finished.	

;;;;; PART 3 ;;;;;
; put the grades into the corret positions
; R1	destination
; R2	to find next filled memory
; R3	nDEST_END
; R4	grade
; R5	only for temp 
		LD		R1, DEST
		LD		R2, DEST
		LD		R3, nDEST_END
		
SORT_LOOP	ADD		R2, R2, #1	
		LDR		R4, R2, #-1	; load the grade to R4 by R2
		BRn		SORT_LOOP	; if the grade is negative(-1), take next

; else find the A/B/C/D for this grade.
; try A
		LD		R5, A_GRADE	
		NOT		R5, R5
		ADD		R5, R5, #1
		ADD		R5, R4, R5	; R5 <- (R4-A_GRADE) 
		BRn		NOTA		; if(R4 < A_GRADE) goto NOTA
		LD		R5, A_RANK
		NOT		R5, R5
		ADD		R5, R5, #1
		ADD		R5, R1, R5	; R5 <- (R1-A_RANK) 
		BRp		NOTA		; else if(R5 > 0) goto NOTA
		LDI		R5, As		; load the address of statistics information.
		ADD		R5, R5, #1	; As++
		STI		R5, As
		BRnzp		LOOP_PRE	
; else try B
NOTA		LD		R5, B_GRADE	
		NOT		R5, R5
		ADD		R5, R5, #1
		ADD		R5, R4, R5	; R5 <- (R4-B_GRADE) 
		BRn		NOTB		; if(R4 < B_GRADE) goto NOTB
		LD		R5, B_RANK
		NOT		R5, R5
		ADD		R5, R5, #1
		ADD		R5, R1, R5	; R5 <- (R1-B_RANK) 
		BRp		NOTA		; else if(R5 > 0) goto NOTB
		LDI		R5, Bs		; load the address of statistics information.
		ADD		R5, R5, #1	; Bs++
		STI		R5, Bs		; store the new Bs
		BRnzp		LOOP_PRE	
; else try D
NOTB		LD		R5, D_GRADE	
		NOT		R5, R5
		ADD		R5, R5, #1
		ADD		R5, R4, R5	; R5 <- (R4-D_GRADE) 
		BRp		NOTD		; if(R4 < D_GRADE) goto NOTD
		LDI		R5, Ds		; load the address of statistics information.
		ADD		R5, R5, #1	; Ds++
		STI		R5, Ds		; store the new Ds
		BRnzp		LOOP_PRE	
; else, C
NOTD		LDI		R5, Cs		; load the address of statistics infsormation.
		ADD		R5, R5, #1	; Cs++
		STI		R5, Cs		; store the new Cs
		
; above finished get the A/B/C/D
LOOP_PRE	STR		R4, R1, #0	; store the grade to the correct position
		ADD		R1, R1, #1	; R1++
		ADD		R5, R3, R1
		BRnz		SORT_LOOP	; 

;;;;; PART 4 ;;;;;
; clear the following into 0
; R1	destination
; R2	nDEST_END100
; R4	0
		
		LD		R2, nDEST_END100
		AND		R4, R4, #0
SET0_LOOP	STR		R4, R1, #0	; store 0 into the position
		ADD		R1, R1, #1	; R1 ++
		ADD		R5, R1, R2	
		BRnz		SET0_LOOP	; check whether finished.

		HALT

A_GRADE		.FILL		#85		; the least grade requirement for A
B_GRADE		.FILL		#75		; the least grade requirement for B
D_GRADE		.FILL		#59		; the grade requirement for D
A_RANK		.FILL		x4011		; the rank requirement for A. Who gets A must be at or before A_RANK.
B_RANK		.FILL		x401C		; the rank requirement for B. Who gets B must be at or before B_RANK.		

GRADE		.FILL		x3200		; the start address of grades
nGRADE_END	.FILL		x-323B		; the opposite number of end address of grades
DEST		.FILL		x4000		; the start address of grades
DEST_END100	.FILL		x4064		; the end address of destination.
nDEST_END100	.FILL		x-4064		; the opposite number of end address of destination.
nDEST_END	.FILL		x-403B		; the opposite number of end address of destination.
As		.FILL		x4100		; the address of number of As.
Bs		.FILL		x4101		; the address of number of Bs.
Cs		.FILL		x4102		; the address of number of Cs.
Ds		.FILL		x4103		; the address of number of Ds.

		.END




