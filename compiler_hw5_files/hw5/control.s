	.file	"control.c"
	.option nopic
	.text
	.section	.rodata
	.align	3
.LC0:
	.string	"correct\n"
	.align	3
.LC1:
	.string	"wrong\n"
	.align	3
.LC3:
	.string	"correct: "
	.align	3
.LC4:
	.string	"\n"
	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sd	ra,24(sp)
	sd	s0,16(sp)
	addi	s0,sp,32
	li	a5,1
	sw	a5,-20(s0)
	sw	zero,-24(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	sext.w	a4,a4
	sext.w	a5,a5
	ble	a4,a5,.L2
	lui	a5,%hi(.LC0)
	addi	a0,a5,%lo(.LC0)
	call	write
	j	.L3
.L2:
	lui	a5,%hi(.LC1)
	addi	a0,a5,%lo(.LC1)
	call	write
.L3:
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	sext.w	a4,a4
	sext.w	a5,a5
	bge	a4,a5,.L4
	lui	a5,%hi(.LC1)
	addi	a0,a5,%lo(.LC1)
	call	write
	j	.L5
.L4:
	lui	a5,%hi(.LC0)
	addi	a0,a5,%lo(.LC0)
	call	write
.L5:
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	sext.w	a4,a4
	sext.w	a5,a5
	bne	a4,a5,.L6
	lui	a5,%hi(.LC1)
	addi	a0,a5,%lo(.LC1)
	call	write
	j	.L7
.L6:
	lui	a5,%hi(.LC0)
	addi	a0,a5,%lo(.LC0)
	call	write
.L7:
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	sext.w	a4,a4
	sext.w	a5,a5
	beq	a4,a5,.L8
	lui	a5,%hi(.LC0)
	addi	a0,a5,%lo(.LC0)
	call	write
	j	.L9
.L8:
	lui	a5,%hi(.LC1)
	addi	a0,a5,%lo(.LC1)
	call	write
.L9:
	lui	a5,%hi(.LC2)
	flw	fa5,%lo(.LC2)(a5)
	fsw	fa5,-28(s0)
	sw	zero,-32(s0)
	flw	fa4,-28(s0)
	flw	fa5,-32(s0)
	fgt.s	a5,fa4,fa5
	beq	a5,zero,.L27
	lui	a5,%hi(.LC0)
	addi	a0,a5,%lo(.LC0)
	call	write
	j	.L12
.L27:
	lui	a5,%hi(.LC1)
	addi	a0,a5,%lo(.LC1)
	call	write
.L12:
	flw	fa4,-28(s0)
	flw	fa5,-32(s0)
	flt.s	a5,fa4,fa5
	beq	a5,zero,.L28
	lui	a5,%hi(.LC1)
	addi	a0,a5,%lo(.LC1)
	call	write
	j	.L15
.L28:
	lui	a5,%hi(.LC0)
	addi	a0,a5,%lo(.LC0)
	call	write
.L15:
	flw	fa4,-28(s0)
	flw	fa5,-32(s0)
	feq.s	a5,fa4,fa5
	bne	a5,zero,.L16
	lui	a5,%hi(.LC0)
	addi	a0,a5,%lo(.LC0)
	call	write
	j	.L17
.L16:
	lui	a5,%hi(.LC1)
	addi	a0,a5,%lo(.LC1)
	call	write
.L17:
	lw	a5,-20(s0)
	sext.w	a5,a5
	beq	a5,zero,.L18
	lw	a5,-24(s0)
	sext.w	a5,a5
	beq	a5,zero,.L18
	lui	a5,%hi(.LC1)
	addi	a0,a5,%lo(.LC1)
	call	write
.L18:
	lw	a5,-20(s0)
	sext.w	a5,a5
	bne	a5,zero,.L19
	lw	a5,-24(s0)
	sext.w	a5,a5
	beq	a5,zero,.L20
.L19:
	lui	a5,%hi(.LC0)
	addi	a0,a5,%lo(.LC0)
	call	write
.L20:
	sw	zero,-20(s0)
	j	.L21
.L22:
	lui	a5,%hi(.LC3)
	addi	a0,a5,%lo(.LC3)
	call	write
	lw	a5,-20(s0)
	mv	a0,a5
	call	write
	lui	a5,%hi(.LC4)
	addi	a0,a5,%lo(.LC4)
	call	write
	lw	a5,-20(s0)
	addiw	a5,a5,1
	sw	a5,-20(s0)
.L21:
	lw	a5,-20(s0)
	sext.w	a4,a5
	li	a5,9
	ble	a4,a5,.L22
	lw	a5,-20(s0)
	sext.w	a4,a5
	li	a5,10
	bne	a4,a5,.L23
	lui	a5,%hi(.LC0)
	addi	a0,a5,%lo(.LC0)
	call	write
.L23:
	li	a5,0
	mv	a0,a5
	ld	ra,24(sp)
	ld	s0,16(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.section	.rodata
	.align	2
.LC2:
	.word	1065353216
	.ident	"GCC: (GNU) 10.2.0"
	.section	.note.GNU-stack,"",@progbits
