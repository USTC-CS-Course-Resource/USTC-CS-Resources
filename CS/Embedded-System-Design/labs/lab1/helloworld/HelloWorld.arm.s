
HelloWorld:     file format elf32-littlearm

Disassembly of section .init:

00008274 <_init>:
_init():
    8274:	e92d4010 	push	{r4, lr}
    8278:	eb000020 	bl	8300 <call_gmon_start>
    827c:	e8bd4010 	pop	{r4, lr}
    8280:	e12fff1e 	bx	lr
Disassembly of section .plt:

00008284 <.plt>:
    8284:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    8288:	e59fe004 	ldr	lr, [pc, #4]	; 8294 <_init+0x20>
    828c:	e08fe00e 	add	lr, pc, lr
    8290:	e5bef008 	ldr	pc, [lr, #8]!
    8294:	000082a4 	.word	0x000082a4
    8298:	e28fc600 	add	ip, pc, #0	; 0x0
    829c:	e28cca08 	add	ip, ip, #32768	; 0x8000
    82a0:	e5bcf2a4 	ldr	pc, [ip, #676]!
    82a4:	e28fc600 	add	ip, pc, #0	; 0x0
    82a8:	e28cca08 	add	ip, ip, #32768	; 0x8000
    82ac:	e5bcf29c 	ldr	pc, [ip, #668]!
    82b0:	e28fc600 	add	ip, pc, #0	; 0x0
    82b4:	e28cca08 	add	ip, ip, #32768	; 0x8000
    82b8:	e5bcf294 	ldr	pc, [ip, #660]!
    82bc:	e28fc600 	add	ip, pc, #0	; 0x0
    82c0:	e28cca08 	add	ip, ip, #32768	; 0x8000
    82c4:	e5bcf28c 	ldr	pc, [ip, #652]!
Disassembly of section .text:

000082c8 <_start>:
_start():
    82c8:	e59fc024 	ldr	ip, [pc, #36]	; 82f4 <_start+0x2c>
    82cc:	e3a0b000 	mov	fp, #0	; 0x0
    82d0:	e49d1004 	pop	{r1}		; (ldr r1, [sp], #4)
    82d4:	e1a0200d 	mov	r2, sp
    82d8:	e52d2004 	push	{r2}		; (str r2, [sp, #-4]!)
    82dc:	e52d0004 	push	{r0}		; (str r0, [sp, #-4]!)
    82e0:	e59f0010 	ldr	r0, [pc, #16]	; 82f8 <_start+0x30>
    82e4:	e59f3010 	ldr	r3, [pc, #16]	; 82fc <_start+0x34>
    82e8:	e52dc004 	push	{ip}		; (str ip, [sp, #-4]!)
    82ec:	ebffffec 	bl	82a4 <_init+0x30>
    82f0:	ebffffe8 	bl	8298 <_init+0x24>
    82f4:	000083a0 	.word	0x000083a0
    82f8:	0000837c 	.word	0x0000837c
    82fc:	000083a4 	.word	0x000083a4

00008300 <call_gmon_start>:
call_gmon_start():
    8300:	e59f301c 	ldr	r3, [pc, #28]	; 8324 <call_gmon_start+0x24>
    8304:	e59f201c 	ldr	r2, [pc, #28]	; 8328 <call_gmon_start+0x28>
    8308:	e08f3003 	add	r3, pc, r3
    830c:	e7931002 	ldr	r1, [r3, r2]
    8310:	e3510000 	cmp	r1, #0	; 0x0
    8314:	e92d4010 	push	{r4, lr}
    8318:	1bffffe4 	blne	82b0 <_init+0x3c>
    831c:	e8bd4010 	pop	{r4, lr}
    8320:	e12fff1e 	bx	lr
    8324:	00008228 	.word	0x00008228
    8328:	0000001c 	.word	0x0000001c

0000832c <__do_global_dtors_aux>:
__do_global_dtors_aux():
    832c:	e59f2010 	ldr	r2, [pc, #16]	; 8344 <__do_global_dtors_aux+0x18>
    8330:	e5d23000 	ldrb	r3, [r2]
    8334:	e3530000 	cmp	r3, #0	; 0x0
    8338:	02833001 	addeq	r3, r3, #1	; 0x1
    833c:	05c23000 	strbeq	r3, [r2]
    8340:	e12fff1e 	bx	lr
    8344:	00010560 	.word	0x00010560

00008348 <frame_dummy>:
frame_dummy():
    8348:	e59f0024 	ldr	r0, [pc, #36]	; 8374 <frame_dummy+0x2c>
    834c:	e5903000 	ldr	r3, [r0]
    8350:	e3530000 	cmp	r3, #0	; 0x0
    8354:	e92d4010 	push	{r4, lr}
    8358:	0a000003 	beq	836c <frame_dummy+0x24>
    835c:	e59f3014 	ldr	r3, [pc, #20]	; 8378 <frame_dummy+0x30>
    8360:	e3530000 	cmp	r3, #0	; 0x0
    8364:	11a0e00f 	movne	lr, pc
    8368:	112fff13 	bxne	r3
    836c:	e8bd4010 	pop	{r4, lr}
    8370:	e12fff1e 	bx	lr
    8374:	0001044c 	.word	0x0001044c
    8378:	00000000 	.word	0x00000000

0000837c <main>:
main():
    837c:	e92d4800 	push	{fp, lr}
    8380:	e28db004 	add	fp, sp, #4	; 0x4
    8384:	e24dd008 	sub	sp, sp, #8	; 0x8
    8388:	e59f000c 	ldr	r0, [pc, #12]	; 839c <main+0x20>
    838c:	ebffffca 	bl	82bc <_init+0x48>
    8390:	e24bd004 	sub	sp, fp, #4	; 0x4
    8394:	e8bd4800 	pop	{fp, lr}
    8398:	e12fff1e 	bx	lr
    839c:	00008428 	.word	0x00008428

000083a0 <__libc_csu_fini>:
__libc_csu_fini():
    83a0:	e12fff1e 	bx	lr

000083a4 <__libc_csu_init>:
__libc_csu_init():
    83a4:	e92d47f0 	push	{r4, r5, r6, r7, r8, r9, sl, lr}
    83a8:	e1a08001 	mov	r8, r1
    83ac:	e1a07002 	mov	r7, r2
    83b0:	e1a0a000 	mov	sl, r0
    83b4:	ebffffae 	bl	8274 <_init>
    83b8:	e59f104c 	ldr	r1, [pc, #76]	; 840c <__libc_csu_init+0x68>
    83bc:	e59f304c 	ldr	r3, [pc, #76]	; 8410 <__libc_csu_init+0x6c>
    83c0:	e59f204c 	ldr	r2, [pc, #76]	; 8414 <__libc_csu_init+0x70>
    83c4:	e0613003 	rsb	r3, r1, r3
    83c8:	e08f2002 	add	r2, pc, r2
    83cc:	e1b05143 	asrs	r5, r3, #2
    83d0:	e0822001 	add	r2, r2, r1
    83d4:	0a00000a 	beq	8404 <__libc_csu_init+0x60>
    83d8:	e1a06002 	mov	r6, r2
    83dc:	e3a04000 	mov	r4, #0	; 0x0
    83e0:	e1a0000a 	mov	r0, sl
    83e4:	e1a01008 	mov	r1, r8
    83e8:	e1a02007 	mov	r2, r7
    83ec:	e796c104 	ldr	ip, [r6, r4, lsl #2]
    83f0:	e1a0e00f 	mov	lr, pc
    83f4:	e12fff1c 	bx	ip
    83f8:	e2844001 	add	r4, r4, #1	; 0x1
    83fc:	e1540005 	cmp	r4, r5
    8400:	3afffff6 	bcc	83e0 <__libc_csu_init+0x3c>
    8404:	e8bd47f0 	pop	{r4, r5, r6, r7, r8, r9, sl, lr}
    8408:	e12fff1e 	bx	lr
    840c:	ffffff0c 	.word	0xffffff0c
    8410:	ffffff10 	.word	0xffffff10
    8414:	00008168 	.word	0x00008168
Disassembly of section .fini:

00008418 <_fini>:
_fini():
    8418:	e92d4010 	push	{r4, lr}
    841c:	e8bd4010 	pop	{r4, lr}
    8420:	e12fff1e 	bx	lr
