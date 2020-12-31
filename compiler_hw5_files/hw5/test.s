	.file	"test.c"
	.option nopic
	.text
	.align	1
	.globl	MAIN
	.type	MAIN, @function
MAIN:
	addi	sp,sp,-32
	sd	s0,24(sp)
	addi	s0,sp,32
	lui	a5,%hi(.LC0)
	flw	fa5,%lo(.LC0)(a5)
	fsw	fa5,-20(s0)
	lui	a5,%hi(.LC1)
	flw	fa5,%lo(.LC1)(a5)
	fsw	fa5,-24(s0)
	flw	fa5,-20(s0)
	fmv.w.x	fa4,zero
	feq.s	a5,fa5,fa4
	bne	a5,zero,.L2
	flw	fa5,-24(s0)
	fmv.w.x	fa4,zero
	feq.s	a5,fa5,fa4
	bne	a5,zero,.L2
	li	a5,3
	sw	a5,-28(s0)
.L2:
	nop
	mv	a0,a5
	ld	s0,24(sp)
	addi	sp,sp,32
	jr	ra
	.size	MAIN, .-MAIN
	.section	.rodata
	.align	2
.LC0:
	.word	-2147483648
	.align	2
.LC1:
	.word	1073741824
	.ident	"GCC: (GNU) 10.2.0"
	.section	.note.GNU-stack,"",@progbits
