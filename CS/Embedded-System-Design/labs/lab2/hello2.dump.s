
hello2:     file format elf32-littlearm

Disassembly of section .interp:

00008134 <.interp>:
    8134:	62696c2f 	rsbvs	r6, r9, #12032	; 0x2f00
    8138:	2d646c2f 	stclcs	12, cr6, [r4, #-188]!
    813c:	756e696c 	strbvc	r6, [lr, #-2412]!
    8140:	6f732e78 	svcvs	0x00732e78
    8144:	Address 0x00008144 is out of bounds.

Disassembly of section .note.ABI-tag:

00008148 <.note.ABI-tag>:
    8148:	00000004 	.word	0x00000004
    814c:	00000010 	.word	0x00000010
    8150:	00000001 	.word	0x00000001
    8154:	00554e47 	.word	0x00554e47
    8158:	00000000 	.word	0x00000000
    815c:	00000002 	.word	0x00000002
    8160:	00000006 	.word	0x00000006
    8164:	0000000e 	.word	0x0000000e
Disassembly of section .hash:

00008168 <.hash>:
    8168:	00000003 	andeq	r0, r0, r3
    816c:	00000004 	andeq	r0, r0, r4
    8170:	00000003 	andeq	r0, r0, r3
    8174:	00000002 	andeq	r0, r0, r2
    8178:	00000001 	andeq	r0, r0, r1
	...
Disassembly of section .dynsym:

0000818c <.dynsym>:
	...
    819c:	0000001a 	andeq	r0, r0, sl, lsl r0
    81a0:	00008274 	andeq	r8, r0, r4, ror r2
    81a4:	000002e4 	andeq	r0, r0, r4, ror #5
    81a8:	00000012 	andeq	r0, r0, r2, lsl r0
    81ac:	00000020 	andeq	r0, r0, r0, lsr #32
    81b0:	00008280 	andeq	r8, r0, r0, lsl #5
    81b4:	0000025c 	andeq	r0, r0, ip, asr r2
    81b8:	00000012 	andeq	r0, r0, r2, lsl r0
    81bc:	00000001 	andeq	r0, r0, r1
	...
    81c8:	00000020 	andeq	r0, r0, r0, lsr #32
Disassembly of section .dynstr:

000081cc <.dynstr>:
    81cc:	675f5f00 	ldrbvs	r5, [pc, -r0, lsl #30]
    81d0:	5f6e6f6d 	svcpl	0x006e6f6d
    81d4:	72617473 	rsbvc	r7, r1, #1929379840	; 0x73000000
    81d8:	005f5f74 	subseq	r5, pc, r4, ror pc
    81dc:	6362696c 	cmnvs	r2, #1769472	; 0x1b0000
    81e0:	2e6f732e 	cdpcs	3, 6, cr7, cr15, cr14, {1}
    81e4:	62610036 	rsbvs	r0, r1, #54	; 0x36
    81e8:	0074726f 	rsbseq	r7, r4, pc, ror #4
    81ec:	696c5f5f 	stmdbvs	ip!, {r0, r1, r2, r3, r4, r6, r8, r9, sl, fp, ip, lr}^
    81f0:	735f6362 	cmpvc	pc, #-2013265919	; 0x88000001
    81f4:	74726174 	ldrbtvc	r6, [r2], #-372
    81f8:	69616d5f 	stmdbvs	r1!, {r0, r1, r2, r3, r4, r6, r8, sl, fp, sp, lr}^
    81fc:	4c47006e 	mcrrmi	0, 6, r0, r7, cr14
    8200:	5f434249 	svcpl	0x00434249
    8204:	00342e32 	eorseq	r2, r4, r2, lsr lr
Disassembly of section .gnu.version:

00008208 <.gnu.version>:
    8208:	00020000 	andeq	r0, r2, r0
    820c:	00000002 	andeq	r0, r0, r2
Disassembly of section .gnu.version_r:

00008210 <.gnu.version_r>:
    8210:	00010001 	andeq	r0, r1, r1
    8214:	00000010 	andeq	r0, r0, r0, lsl r0
    8218:	00000010 	andeq	r0, r0, r0, lsl r0
    821c:	00000000 	andeq	r0, r0, r0
    8220:	0d696914 	stcleq	9, cr6, [r9, #-80]!
    8224:	00020000 	andeq	r0, r2, r0
    8228:	00000032 	andeq	r0, r0, r2, lsr r0
    822c:	00000000 	andeq	r0, r0, r0
Disassembly of section .rel.dyn:

00008230 <.rel.dyn>:
    8230:	00010510 	andeq	r0, r1, r0, lsl r5
    8234:	00000315 	andeq	r0, r0, r5, lsl r3
Disassembly of section .rel.plt:

00008238 <.rel.plt>:
    8238:	00010504 	andeq	r0, r1, r4, lsl #10
    823c:	00000116 	andeq	r0, r0, r6, lsl r1
    8240:	00010508 	andeq	r0, r1, r8, lsl #10
    8244:	00000216 	andeq	r0, r0, r6, lsl r2
    8248:	0001050c 	andeq	r0, r1, ip, lsl #10
    824c:	00000316 	andeq	r0, r0, r6, lsl r3
Disassembly of section .init:

00008250 <_init>:
    8250:	e92d4010 	push	{r4, lr}
    8254:	eb00001d 	bl	82d0 <call_gmon_start>
    8258:	e8bd4010 	pop	{r4, lr}
    825c:	e12fff1e 	bx	lr
Disassembly of section .plt:

00008260 <.plt>:
    8260:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    8264:	e59fe004 	ldr	lr, [pc, #4]	; 8270 <_init+0x20>
    8268:	e08fe00e 	add	lr, pc, lr
    826c:	e5bef008 	ldr	pc, [lr, #8]!
    8270:	00008288 	.word	0x00008288
    8274:	e28fc600 	add	ip, pc, #0	; 0x0
    8278:	e28cca08 	add	ip, ip, #32768	; 0x8000
    827c:	e5bcf288 	ldr	pc, [ip, #648]!
    8280:	e28fc600 	add	ip, pc, #0	; 0x0
    8284:	e28cca08 	add	ip, ip, #32768	; 0x8000
    8288:	e5bcf280 	ldr	pc, [ip, #640]!
    828c:	e28fc600 	add	ip, pc, #0	; 0x0
    8290:	e28cca08 	add	ip, ip, #32768	; 0x8000
    8294:	e5bcf278 	ldr	pc, [ip, #632]!
Disassembly of section .text:

00008298 <_start>:
    8298:	e59fc024 	ldr	ip, [pc, #36]	; 82c4 <_start+0x2c>
    829c:	e3a0b000 	mov	fp, #0	; 0x0
    82a0:	e49d1004 	pop	{r1}		; (ldr r1, [sp], #4)
    82a4:	e1a0200d 	mov	r2, sp
    82a8:	e52d2004 	push	{r2}		; (str r2, [sp, #-4]!)
    82ac:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
    82b0:	e59f0010 	ldr	r0, [pc, #16]	; 82c8 <_start+0x30>
    82b4:	e59f3010 	ldr	r3, [pc, #16]	; 82cc <_start+0x34>
    82b8:	e52dc004 	push	{ip}		; (str ip, [sp, #-4]!)
    82bc:	ebffffef 	bl	8280 <_init+0x30>
    82c0:	ebffffeb 	bl	8274 <_init+0x24>
    82c4:	00008370 	.word	0x00008370
    82c8:	0000834c 	.word	0x0000834c
    82cc:	00008374 	.word	0x00008374

000082d0 <call_gmon_start>:
    82d0:	e59f301c 	ldr	r3, [pc, #28]	; 82f4 <call_gmon_start+0x24>
    82d4:	e59f201c 	ldr	r2, [pc, #28]	; 82f8 <call_gmon_start+0x28>
    82d8:	e08f3003 	add	r3, pc, r3
    82dc:	e7931002 	ldr	r1, [r3, r2]
    82e0:	e3510000 	cmp	r1, #0	; 0x0
    82e4:	e92d4010 	push	{r4, lr}
    82e8:	1bffffe7 	blne	828c <_init+0x3c>
    82ec:	e8bd4010 	pop	{r4, lr}
    82f0:	e12fff1e 	bx	lr
    82f4:	00008218 	.word	0x00008218
    82f8:	00000018 	.word	0x00000018

000082fc <__do_global_dtors_aux>:
    82fc:	e59f2010 	ldr	r2, [pc, #16]	; 8314 <__do_global_dtors_aux+0x18>
    8300:	e5d23000 	ldrb	r3, [r2]
    8304:	e3530000 	cmp	r3, #0	; 0x0
    8308:	02833001 	addeq	r3, r3, #1	; 0x1
    830c:	05c23000 	strbeq	r3, [r2]
    8310:	e12fff1e 	bx	lr
    8314:	0001052a 	.word	0x0001052a

00008318 <frame_dummy>:
    8318:	e59f0024 	ldr	r0, [pc, #36]	; 8344 <frame_dummy+0x2c>
    831c:	e5903000 	ldr	r3, [r0]
    8320:	e3530000 	cmp	r3, #0	; 0x0
    8324:	e92d4010 	push	{r4, lr}
    8328:	0a000003 	beq	833c <frame_dummy+0x24>
    832c:	e59f3014 	ldr	r3, [pc, #20]	; 8348 <frame_dummy+0x30>
    8330:	e3530000 	cmp	r3, #0	; 0x0
    8334:	11a0e00f 	movne	lr, pc
    8338:	112fff13 	bxne	r3
    833c:	e8bd4010 	pop	{r4, lr}
    8340:	e12fff1e 	bx	lr
    8344:	0001040c 	.word	0x0001040c
    8348:	00000000 	.word	0x00000000

0000834c <main>:
    834c:	e3a00001 	mov	r0, #1	; 0x1
    8350:	e59f1014 	ldr	r1, [pc, #20]	; 836c <main+0x20>
    8354:	e3a0200e 	mov	r2, #14	; 0xe
    8358:	e3a07004 	mov	r7, #4	; 0x4
    835c:	ef000000 	svc	0x00000000
    8360:	e3a00000 	mov	r0, #0	; 0x0
    8364:	e3a07001 	mov	r7, #1	; 0x1
    8368:	ef000000 	svc	0x00000000
    836c:	0001051c 	.word	0x0001051c

00008370 <__libc_csu_fini>:
    8370:	e12fff1e 	bx	lr

00008374 <__libc_csu_init>:
    8374:	e92d47f0 	push	{r4, r5, r6, r7, r8, r9, sl, lr}
    8378:	e1a08001 	mov	r8, r1
    837c:	e1a07002 	mov	r7, r2
    8380:	e1a0a000 	mov	sl, r0
    8384:	ebffffb1 	bl	8250 <_init>
    8388:	e59f104c 	ldr	r1, [pc, #76]	; 83dc <__libc_csu_init+0x68>
    838c:	e59f304c 	ldr	r3, [pc, #76]	; 83e0 <__libc_csu_init+0x6c>
    8390:	e59f204c 	ldr	r2, [pc, #76]	; 83e4 <__libc_csu_init+0x70>
    8394:	e0613003 	rsb	r3, r1, r3
    8398:	e08f2002 	add	r2, pc, r2
    839c:	e1b05143 	asrs	r5, r3, #2
    83a0:	e0822001 	add	r2, r2, r1
    83a4:	0a00000a 	beq	83d4 <__libc_csu_init+0x60>
    83a8:	e1a06002 	mov	r6, r2
    83ac:	e3a04000 	mov	r4, #0	; 0x0
    83b0:	e1a0000a 	mov	r0, sl
    83b4:	e1a01008 	mov	r1, r8
    83b8:	e1a02007 	mov	r2, r7
    83bc:	e796c104 	ldr	ip, [r6, r4, lsl #2]
    83c0:	e1a0e00f 	mov	lr, pc
    83c4:	e12fff1c 	bx	ip
    83c8:	e2844001 	add	r4, r4, #1	; 0x1
    83cc:	e1540005 	cmp	r4, r5
    83d0:	3afffff6 	bcc	83b0 <__libc_csu_init+0x3c>
    83d4:	e8bd47f0 	pop	{r4, r5, r6, r7, r8, r9, sl, lr}
    83d8:	e12fff1e 	bx	lr
    83dc:	ffffff0c 	.word	0xffffff0c
    83e0:	ffffff10 	.word	0xffffff10
    83e4:	00008158 	.word	0x00008158
Disassembly of section .fini:

000083e8 <_fini>:
    83e8:	e92d4010 	push	{r4, lr}
    83ec:	e8bd4010 	pop	{r4, lr}
    83f0:	e12fff1e 	bx	lr
Disassembly of section .rodata:

000083f4 <_IO_stdin_used>:
    83f4:	00020001 	.word	0x00020001
Disassembly of section .ARM.exidx:

000083f8 <.ARM.exidx>:
    83f8:	7ffffea0 	svcvc	0x00fffea0
    83fc:	00000001 	andeq	r0, r0, r1
Disassembly of section .eh_frame:

00008400 <__FRAME_END__>:
    8400:	00000000 	.word	0x00000000
Disassembly of section .init_array:

00010404 <__frame_dummy_init_array_entry>:
   10404:	00008318 	.word	0x00008318
Disassembly of section .fini_array:

00010408 <__do_global_dtors_aux_fini_array_entry>:
   10408:	000082fc 	.word	0x000082fc
Disassembly of section .jcr:

0001040c <__JCR_END__>:
   1040c:	00000000 	.word	0x00000000
Disassembly of section .dynamic:

00010410 <_DYNAMIC>:
   10410:	00000001 	.word	0x00000001
   10414:	00000010 	.word	0x00000010
   10418:	0000000c 	.word	0x0000000c
   1041c:	00008250 	.word	0x00008250
   10420:	0000000d 	.word	0x0000000d
   10424:	000083e8 	.word	0x000083e8
   10428:	00000019 	.word	0x00000019
   1042c:	00010404 	.word	0x00010404
   10430:	0000001b 	.word	0x0000001b
   10434:	00000004 	.word	0x00000004
   10438:	0000001a 	.word	0x0000001a
   1043c:	00010408 	.word	0x00010408
   10440:	0000001c 	.word	0x0000001c
   10444:	00000004 	.word	0x00000004
   10448:	00000004 	.word	0x00000004
   1044c:	00008168 	.word	0x00008168
   10450:	00000005 	.word	0x00000005
   10454:	000081cc 	.word	0x000081cc
   10458:	00000006 	.word	0x00000006
   1045c:	0000818c 	.word	0x0000818c
   10460:	0000000a 	.word	0x0000000a
   10464:	0000003c 	.word	0x0000003c
   10468:	0000000b 	.word	0x0000000b
   1046c:	00000010 	.word	0x00000010
   10470:	00000015 	.word	0x00000015
   10474:	00000000 	.word	0x00000000
   10478:	00000003 	.word	0x00000003
   1047c:	000104f8 	.word	0x000104f8
   10480:	00000002 	.word	0x00000002
   10484:	00000018 	.word	0x00000018
   10488:	00000014 	.word	0x00000014
   1048c:	00000011 	.word	0x00000011
   10490:	00000017 	.word	0x00000017
   10494:	00008238 	.word	0x00008238
   10498:	00000011 	.word	0x00000011
   1049c:	00008230 	.word	0x00008230
   104a0:	00000012 	.word	0x00000012
   104a4:	00000008 	.word	0x00000008
   104a8:	00000013 	.word	0x00000013
   104ac:	00000008 	.word	0x00000008
   104b0:	6ffffffe 	.word	0x6ffffffe
   104b4:	00008210 	.word	0x00008210
   104b8:	6fffffff 	.word	0x6fffffff
   104bc:	00000001 	.word	0x00000001
   104c0:	6ffffff0 	.word	0x6ffffff0
   104c4:	00008208 	.word	0x00008208
	...
Disassembly of section .got:

000104f8 <_GLOBAL_OFFSET_TABLE_>:
   104f8:	00010410 	.word	0x00010410
	...
   10504:	00008260 	.word	0x00008260
   10508:	00008260 	.word	0x00008260
   1050c:	00008260 	.word	0x00008260
   10510:	00000000 	.word	0x00000000
Disassembly of section .data:

00010514 <__data_start>:
   10514:	00000000 	.word	0x00000000

00010518 <__dso_handle>:
   10518:	00000000 	.word	0x00000000

0001051c <msg>:
   1051c:	6c6c6568 	.word	0x6c6c6568
   10520:	77202c6f 	.word	0x77202c6f
   10524:	646c726f 	.word	0x646c726f
   10528:	000a      	.short	0x000a
Disassembly of section .bss:

0001052a <completed.5877>:
	...
Disassembly of section .debug_frame:

00000000 <.debug_frame>:
   0:	0000000c 	andeq	r0, r0, ip
   4:	ffffffff 	undefined instruction 0xffffffff
   8:	7c010001 	stcvc	0, cr0, [r1], {1}
   c:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  10:	0000000c 	andeq	r0, r0, ip
  14:	00000000 	andeq	r0, r0, r0
  18:	00008370 	andeq	r8, r0, r0, ror r3
  1c:	00000004 	andeq	r0, r0, r4
  20:	00000020 	andeq	r0, r0, r0, lsr #32
  24:	00000000 	andeq	r0, r0, r0
  28:	00008374 	andeq	r8, r0, r4, ror r3
  2c:	00000074 	andeq	r0, r0, r4, ror r0
  30:	8e200e44 	cdphi	14, 2, cr0, cr0, cr4, {2}
  34:	89028a01 	stmdbhi	r2, {r0, r9, fp, pc}
  38:	87048803 	strhi	r8, [r4, -r3, lsl #16]
  3c:	85068605 	strhi	r8, [r6, #-1541]
  40:	00088407 	andeq	r8, r8, r7, lsl #8
Disassembly of section .ARM.attributes:

00000000 <.ARM.attributes>:
   0:	00002741 	andeq	r2, r0, r1, asr #14
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	0000001d 	andeq	r0, r0, sp, lsl r0
  10:	00543405 	subseq	r3, r4, r5, lsl #8
  14:	01080206 	tsteq	r8, r6, lsl #4
  18:	04120109 	ldreq	r0, [r2], #-265
  1c:	01150114 	tsteq	r5, r4, lsl r1
  20:	01180317 	tsteq	r8, r7, lsl r3
  24:	021a0119 	andseq	r0, sl, #1073741830	; 0x40000006
