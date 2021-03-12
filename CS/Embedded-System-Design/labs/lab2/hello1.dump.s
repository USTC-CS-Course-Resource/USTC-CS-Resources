
hello1:     file format elf32-littlearm

Disassembly of section .text:

00008074 <_start>:
    8074:	e3a00001 	mov	r0, #1	; 0x1
    8078:	e59f1014 	ldr	r1, [pc, #20]	; 8094 <_start+0x20>
    807c:	e3a0200e 	mov	r2, #14	; 0xe
    8080:	e3a07004 	mov	r7, #4	; 0x4
    8084:	ef000000 	svc	0x00000000
    8088:	e3a00000 	mov	r0, #0	; 0x0
    808c:	e3a07001 	mov	r7, #1	; 0x1
    8090:	ef000000 	svc	0x00000000
    8094:	00010098 	.word	0x00010098
Disassembly of section .data:

00010098 <__data_start>:
   10098:	6c6c6568 	.word	0x6c6c6568
   1009c:	77202c6f 	.word	0x77202c6f
   100a0:	646c726f 	.word	0x646c726f
   100a4:	000a      	.short	0x000a
Disassembly of section .ARM.attributes:

00000000 <.ARM.attributes>:
   0:	00001341 	andeq	r1, r0, r1, asr #6
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	00000009 	andeq	r0, r0, r9
  10:	01080106 	tsteq	r8, r6, lsl #2
