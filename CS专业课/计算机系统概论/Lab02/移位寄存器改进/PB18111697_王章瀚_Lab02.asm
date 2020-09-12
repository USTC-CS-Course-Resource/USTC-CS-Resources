		.ORIG		x3000
		LD		R0, Nx8A9C
		LD		R3, Nxn8000	
		AND		R4, R4, #0
		AND		R0, R0, #-2
		ADD		R0, R0, #1
		BRzp		START
		ADD		R4, R4, #-1
		BRnzp		START

P		ADD		R4, R4, R4
		ADD		R0, R0, R0
CHECK_P		BRp		P
		ADD		R1, R0, R3
		BRp		N
		BRnzp		OK
N		ADD		R4, R4, R4
		ADD		R4, R4, #1
START		ADD		R0, R0, R0
CHECK_N		BRp		P
		ADD		R1, R0, R3
		BRp		N
		BRnzp		OK

OK		HALT

Nx8A9C		.FILL		xAFFF
Nxn8000		.FILL		x-8000
NxnC000		.FILL		x-C000
		.END