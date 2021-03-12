PLAT=arm-linux-
AS=$(PLAT)as
CC=$(PLAT)gcc

sort: main.c strsort.o
	$(CC) main.c strsort.o -o sort

strsort: strsort.s
	$(AS) strsort.s -o strsort.o