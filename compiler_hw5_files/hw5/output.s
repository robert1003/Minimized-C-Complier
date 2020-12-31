	.section .sdata,"aw"
	.section .sbss,"aw",@nobits
	.text
	.align 1
	.globl MAIN
	.type MAIN, @function
MAIN:
	fmv.w.x ft0,zero
	sd ra,-8(sp)
	sd fp,-16(sp)
	addi fp,sp,-16
	addi sp,sp,-16
	addi sp,sp,-64
	sw s1,-4(fp)
	sw s2,-8(fp)
	sw s3,-12(fp)
	sw s4,-16(fp)
	sw s5,-20(fp)
	sw s6,-24(fp)
	sw s7,-28(fp)
	call _read_int
	mv t0, a0
	lw s1,-32(fp)
	mv s1, t0
	call _read_int
	mv t0, a0
	lw s2,-36(fp)
	mv s2, t0
	addi t0, zero, 2
	add t1, s1, t0
	lw s3,-40(fp)
	mv s3, t1
	addi t0, zero, 4
	add t1, s2, t0
	lw s4,-44(fp)
	mv s4, t1
	addi t0, zero, 1
	add t1, s1, t0
	lw s5,-48(fp)
	mv s5, t1
	lw s6,-52(fp)
	mv s6, s2
	mul t0, s3, s4
	addi t1, zero, 1
	sub t2, t0, t1
	lw s7,-56(fp)
	mv s7, t2
	sw s1,-32(fp)
	sw s2,-36(fp)
	sw s3,-40(fp)
	sw s4,-44(fp)
	sw s5,-48(fp)
	sw s6,-52(fp)
	sw s7,-56(fp)
_IF_5:
	lw s1,-32(fp)
	lw s2,-36(fp)
	bnez s1, _OR_true_6
	beqz s2, _OR_false_6
_OR_true_6:
	li t0, 1
j _OR_end_6
_OR_false_6:
	li t0, 0
_OR_end_6:
	lw s3,-40(fp)
	lw s4,-44(fp)
	beqz s3, _AND_false_7
	beqz s4, _AND_false_7
_AND_true_7:
	li t1, 1
j _AND_end_7
_AND_false_7:
	li t1, 0
_AND_end_7:
	lw s5,-48(fp)
	addi t2, zero, 1
	sub t3, s5, t2
	sgtz t3, t3
	beqz t1, _AND_false_8
	beqz t3, _AND_false_8
_AND_true_8:
	li t2, 1
j _AND_end_8
_AND_false_8:
	li t2, 0
_AND_end_8:
	bnez t0, _OR_true_9
	beqz t2, _OR_false_9
_OR_true_9:
	li t1, 1
j _OR_end_9
_OR_false_9:
	li t1, 0
_OR_end_9:
	lw s6,-52(fp)
	addi t0, zero, 1
	sub t2, s6, t0
	sgtz t2, t2
	lw s7,-56(fp)
	addi t0, zero, 1
	sub t3, s7, t0
	sltz t3, t3
	beqz t2, _AND_false_10
	beqz t3, _AND_false_10
_AND_true_10:
	li t0, 1
j _AND_end_10
_AND_false_10:
	li t0, 0
_AND_end_10:
	bnez t1, _OR_true_11
	beqz t0, _OR_false_11
_OR_true_11:
	li t2, 1
j _OR_end_11
_OR_false_11:
	li t2, 0
_OR_end_11:
	beqz t2, _ELSE_5
	lui t0,%hi(.LC12)
	addi a0,t0,%lo(.LC12)
	call _write_str
	j _EXIT_5
_ELSE_5:
	lui t0,%hi(.LC13)
	addi a0,t0,%lo(.LC13)
	call _write_str
_EXIT_5:
	addi t0, zero, 0
	mv a0, t0
	j MAIN_EXIT_
MAIN_EXIT_:
	lw s7,-28(fp)
	lw s6,-24(fp)
	lw s5,-20(fp)
	lw s4,-16(fp)
	lw s3,-12(fp)
	lw s2,-8(fp)
	lw s1,-4(fp)
	ld ra,8(fp)
	addi sp,fp,16
	ld fp,0(fp)
	jr ra
	.size MAIN, .-MAIN
	.section .rodata
	.align 3
.LC13:
	.string "False \n\000"
	.align 3
.LC12:
	.string "True \n\000"
