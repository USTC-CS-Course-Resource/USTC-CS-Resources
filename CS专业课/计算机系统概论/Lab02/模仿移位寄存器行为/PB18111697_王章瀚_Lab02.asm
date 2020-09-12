		.ORIG		x3000
		LD		R1, Nx000E	; serve as a counter
		LD		R3, NxFFFE
		AND		R0, R0, R3 	; set R0[0] to 0
		LD		R3, Nx8000
		AND		R3, R0, R3
		BRzp		LOOP		; check the sign of R0
		ADD		R0, R0, #1

LOOP		ADD		R0, R0, R0	; shift left
		BRzp		ZP
		ADD		R0, R0, #1	; if R[15] is 1, R[0] <- 1
ZP		ADD		R1, R1, #-1	
		BRp		LOOP
		
		AND		R0, R0, R0
		BRn		OK
		AND		R3, R3, R3
		BRzp		OK
		ADD		R0, R0, R3	; these set the sign of R0

OK		HALT

Nx000E		.FILL		x000E
NxFFFE		.FILL		xFFFE
Nx8000		.FILL		x8000
		.END